//////////////////////////////////////////////////
// (c) 2016 white LayerManager.cpp
//////////////////////////////////////////////////


//////////////////////////////////////////////////
// Header file is LayerManager.hpp
// namespace is jubeon::graphics
//////////////////////////////////////////////////

//for header file
#include "LayerManager.hpp"

//for logger
#include "Systems/Logger.hpp"

//for thread sleep
#include <thread>
#include <chrono>

//using namespace
using namespace jubeon::graphics;

//static defition
const sf::Vector2u jubeon::graphics::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768, 1360);
std::unordered_map<std::string, LayerManager *> jubeon::graphics::LayerManager::layermanager_map;

//Constructor with arguments
jubeon::graphics::LayerManager::LayerManager(const std::string & mapping_name, const LayoutType window_type)
	: layout_type(window_type)
{
    //create window buffer
	if (!this->window_buffer.create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y)) {
		jubeon::systems::Logger::error("Failed to create the window render buffer.");
		return;
	}
	this->window_buffer.clear();
	this->window_buffer.setSmooth(true);
	
	//layer mapping
	this->layermanager_map[mapping_name] = this;
}


//Destructor
jubeon::graphics::LayerManager::~LayerManager()
{

}

//レイヤーの追加
void jubeon::graphics::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{
	//まずレイヤーの初期化を行う。
	layer->Init();

	//同じタイプでレイヤーナンバーの場所に入れる
	unsigned char i = 0;
	std::vector<std::shared_ptr<LayerBase>>::iterator  p;
	for (p = this->layer_list.begin(); p != this->layer_list.end(); p++) {

		//同じタイプかどうかマッピングを確認する
		if (this->layer_map[*p] == type) {
			if (i == layernumber) break;	//番号が同じであれば、そこが挿入する場所
			i++;	//そうでなければ番号をインクリメント
		}
		else if (this->layer_map[*p] > type) break;	//飛ばして次へ行っていた、つまり問答無用で挿入場所

	}

	//新しく挿入する
	this->layer_map[layer] = type;
	this->layer_list.insert(p, layer);

}


//ウィンドウを終了させる
void jubeon::graphics::LayerManager::closeWindow(void)
{
	
	//まずすべてのExitを呼ぶ
	for (auto p = this->layer_list.begin(); p != this->layer_list.end(); p++) {
		(*p)->setExitCode(1);
		(*p)->Exit();
	}

	this->close();
}


//レイヤー描写
void jubeon::graphics::LayerManager::process(void) {


	this->window_buffer.clear();


	if (this->layer_list.size() > 0) {
		for (auto p = --this->layer_list.end(); ; p--) {
			(*p)->createBuffer(this->RENDER_TEXTURE_SIZE);

			//描写
			(*p)->Draw();

			//終了検知
			if ((*p)->getExitCode() != 0) {
				//終了処理
				(*p)->Exit();
				//リストから削除
				//デクリメントだから全ループにおいてp--が可能
				p = this->layer_list.erase(p);
			}
			else {				
				this->window_buffer.draw((*p)->getSprite());
			}

			if (p == this->layer_list.begin()) break;	//全てのレイヤーを描写済み
		}
	}




	//ウィンドウバッファのアップデート
	window_buffer.display();

	//スプライトの作成
	sf::Sprite wsp(window_buffer.getTexture());

	//スプライトごにょごにょ
	sf::Vector2f scale;

	sf::Vector2u size = window_buffer.getSize();
	float rotate = 0.0f;

	if (this->layout_type == LayoutType::Y_PLUS) {
		unsigned int n = size.x;
		size.x = size.y;
		size.y = n;
		rotate = 90.0f;
	}
	else if (this->layout_type == LayoutType::X_MINUS) {
		rotate = 180.0f;
	}
	else if (this->layout_type == LayoutType::Y_MINUS) {
		rotate = 270.0f;
		unsigned int n = size.x;
		size.x = size.y;
		size.y = n;
	}
	

	scale.x = static_cast<float>(this->getSize().x) / static_cast<float>(size.x);
	scale.y = static_cast<float>(this->getSize().y) / static_cast<float>(size.y);

	if (scale.x > scale.y) scale.x = scale.y;
	else scale.y = scale.x;

	wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
	wsp.setPosition(this->getSize().x / 2.0f, this->getSize().y / 2.0f);
	wsp.setRotation(rotate);
	wsp.setScale(scale);

    { //mutable area
        std::lock_guard<std::mutex> lock(this->mtx);
        
        //Clear Window
	    this->clear();

	    //Draw Window
	    this->draw(wsp);

	    //Update Window
	    this->display();
    }
    
}

void jubeon::graphics::LayerManager::eventLoop(void)
{
	bool is_exit = false;

	this->setKeyRepeatEnabled(false);

	while (!is_exit && this->isOpen()) {
		sf::Event e;
		if (!this->waitEvent(e)) break;

		if (e.type == sf::Event::KeyPressed && e.key.alt == true && e.key.code == sf::Keyboard::F4) break;

		if (this->event_cb) this->event_cb(e);
	}

	systems::Logger::information("Closed event queuing function.");
}

void jubeon::graphics::LayerManager::setCallback(Callback function)
{
	{ //Mutable Area
		std::lock_guard<std::mutex> lock(this->mtx);
		this->event_cb = function;
	}
}


jubeon::graphics::LayerManager * jubeon::graphics::LayerManager::getInstance(const std::string & name){
    return layermanager_map.at(name);
}

void jubeon::graphics::LayerManager::processAll(void){
    for(auto p : layermanager_map){
        p.second->process();
    }
}

