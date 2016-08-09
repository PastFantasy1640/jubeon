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

//using namespace
using namespace jubeon::graphics;

//static defition
const sf::Vector2u jubeon::graphics::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768, 1360);

//Constructor with arguments
jubeon::graphics::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const bool isVSync,
	const unsigned int fpsLimit,
	const sf::Vector2i startWindowPosition,
	const sf::Uint32 style)
	: vmode(vmode),
	window_title(window_title),
	window_style(style),
	isVSync(isVSync),
	fpsLimit(fpsLimit),
	window_position(startWindowPosition),
	is_open_window(false)
{
}

//Destructor
jubeon::graphics::LayerManager::~LayerManager()
{
	//あえてリリースする必要は無い？
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

void jubeon::graphics::LayerManager::createWindow(void)
{
	//まずウィンドウを生成
	this->window.reset(new sf::RenderWindow(this->vmode, this->window_title, this->window_style));
	this->window->clear();

	this->window->setVerticalSyncEnabled(this->isVSync);
	this->window->setFramerateLimit(this->fpsLimit);
	this->window->setPosition(this->window_position);
//	this->window->setActive(false);
	
	//ウィンドウバッファの生成
	if (!this->window_buffer.create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y)) {
		jubeon::systems::Logger::error("ウィンドウバッファの生成に失敗しました");
		return;
	}
	this->window_buffer.clear();
	this->window_buffer.setSmooth(true);
}

//ウィンドウが開いているか
bool jubeon::graphics::LayerManager::isWindowOpening(void) const
{
	return this->window->isOpen();
}

//ウィンドウを終了させる
void jubeon::graphics::LayerManager::closeWindow(void)
{
	
	//まずすべてのExitを呼ぶ
	for (auto p = this->layer_list.begin(); p != this->layer_list.end(); p++) {
		(*p)->setExitCode(1);
		(*p)->Exit();
	}

	this->window->close();
}

bool jubeon::graphics::LayerManager::getWindowEvent(sf::Event & e)
{
	return this->window->pollEvent(e);
}

//レイヤー描写
void jubeon::graphics::LayerManager::process(void) {


	this->window_buffer.clear();
	this->window->clear(sf::Color::Black);



	if (this->layer_list.size() > 0) {
		for (auto p = --this->layer_list.end(); ; p--) {
			(*p)->prepareBuffer(this->RENDER_TEXTURE_SIZE);

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

				//画面更新
				(*p)->display();

				//sf::Sprite sp((*p)->getTexture());
				//this->window->draw(sp);
				//ウィンドウバッファに描写
				this->window_buffer.draw(sf::Sprite((*p)->getTexture()));
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
	scale.x = static_cast<float>(this->window->getSize().x) / static_cast<float>(window_buffer.getSize().x);
	scale.y = static_cast<float>(this->window->getSize().y) / static_cast<float>(window_buffer.getSize().y);

	if (scale.x > scale.y) scale.x = scale.y;
	else scale.y = scale.x;

	wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
	wsp.setPosition(this->vmode.width / 2.0f, this->vmode.height / 2.0f);
	wsp.setScale(scale);

	//画面描写
	this->window->draw(wsp);


	//画面アップデート
	this->window->display();

	//もしも垂直同期無しでfps制限もないとき、少し待つ
	if (this->isVSync == false && this->fpsLimit == 0) std::this_thread::sleep_for(std::chrono::microseconds(1));


}

