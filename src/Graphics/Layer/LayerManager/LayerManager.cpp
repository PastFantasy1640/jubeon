/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "../LayerBase/LayerBase.hpp"
#include <exception>
#include "../../../systems/exceptions/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;


//#############  コンストラクタ　・　デストラクタ  ###############

jubeat_online::graphics::layer::LayerManager::LayerManager()
	: layer_list(nullptr),
	vmode(LAYERMANAGER_DEFAULT_WINDOW_WIDTH, LAYERMANAGER_DEFAULT_WINDOW_HEIGHT),
	window_title("Untitled window"),
	window_style(sf::Style::Default),
	scale(1.0f)
{

	//ウィンドウの生成は別。

	//リストインスタンスの生成
	try {
		this->layer_list.reset(new std::list<LayerDetail>);

		if (this->layer_list == nullptr) throw std::bad_alloc();
	}
	catch (std::bad_alloc e) {
		this->layer_list = nullptr;
		//メモリの確保に失敗した場合再スロー
		throw jubeat_online::systems::exceptions::bad_alloc(
			"LayerManagerにおいてレイヤーリスト用の領域確保に失敗しました。メモリに十分な空きがあるか確認してください。");
	}
}




jubeat_online::graphics::layer::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const sf::Uint32 style)
	: LayerManager()
{

	//デフォルト値のウィンドウ情報の更新
	this->vmode = vmode;
	this->window_style = style;
	this->window_title = window_title;

}





jubeat_online::graphics::layer::LayerManager::~LayerManager()
{
	//全てのレイヤーの解放
	for (std::list<LayerDetail>::iterator p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		if ((*p).lb != nullptr) {
			(*p).lb->Exit();
			delete (*p).lb;
			(*p).lb = nullptr;
		}

		p = this->layer_list->erase(p);
	}

	//リストの解放
	//delete this->layer_list;
	//this->layer_list = nullptr;

	//ウィンドウの終了
	this->window.close();
}


//#############  ウィンドウの生成  ###############

void jubeat_online::graphics::layer::LayerManager::createWindow(void)
{

	this->window.setVerticalSyncEnabled(true);

	this->window.create(this->vmode, this->window_title, this->window_style);
	this->window.clear();

	//#################TEMPORARY
	this->window.setPosition(sf::Vector2i(0, 0));
	this->window.setVerticalSyncEnabled(true);
}

void jubeat_online::graphics::layer::LayerManager::setScale(const double rate)
{
	this->scale = rate;
	sf::Vector2u size = this->window.getSize();
	size.x *= rate;
	size.y *= rate;
	this->window.setSize(size);
}


//#############  レイヤーの追加  ###############

void jubeat_online::graphics::layer::LayerManager::addLayer(LayerBase * layer, const LayerType type, const unsigned char layernumber)
{
	//レイヤーの追加
	//同じタイプでレイヤーナンバーの場所に入れる
	unsigned char i = 0;
	std::list<LayerDetail>::iterator  p;
	for (p = this->layer_list->begin(); p != this->layer_list->end(); p++) {
		if ((*p).lt == type) {
			if (i == layernumber) break;
			i++;
		}
		else if ((*p).lt > type) break;
	}

	LayerDetail newlb;
	newlb.lb = layer;
	newlb.lt = type;

	this->layer_list->insert(p,newlb);

	//layer->createScreenBuffer(this->window.getSize().x, this->window.getSize().y);
	
	layer->create(this->vmode.width, this->vmode.height, false);
	layer->setSmooth(true);
	layer->Init();
}


//#############  レイヤー描写フロー  ###############
void jubeat_online::graphics::layer::LayerManager::process(void)
{



	while (this->window.isOpen()) {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			//「クローズが要求された」イベント：ウインドウを閉じる
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) this->window.close();
		}


		this->window.clear();
		if (this->layer_list->size() > 0) {
			for (std::list<LayerDetail>::iterator p = --this->layer_list->end(); /*p != this->layer_list->end()*/; p--) {
				//描写
				p->lb->Draw();

				p->lb->display();
				sf::Sprite sp(p->lb->getTexture());
				//sp.setTexture(*p->lb->getScreenBufferTexture());
				//sp.setPosition(0, 0);
				if (this->scale != 1.0f) {
					//sp.setScale(1.0f / this->scale, 1.0f / this->scale);
					sp.setScale(1, 1);
				}
				this->window.draw(sp);

				if (p->lb->getExitCode() != 0) {
					//終了処理
					p->lb->Exit();
					//リストから削除
					p = this->layer_list->erase(p);
				}
				//else p--;
				if (p == this->layer_list->begin()) break;	//全てのレイヤーを描写済み
			}
		}

		window.display();   //描画アップデート
	}


	for (std::list<LayerDetail>::iterator p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		p->lb->Exit();
		p = this->layer_list->erase(p);
	}

	//レイヤー全てをExitする。
	//listは開放しない
	//それぞれのレイヤーも解放しない
}
