/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "LayerBase.hpp"
#include <exception>
#include <thread>
#include "../../Systems/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;

const sf::Vector2u jubeat_online::graphics::layer::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768,1360);

//#############  コンストラクタ　・　デストラクタ  ###############

jubeat_online::graphics::layer::LayerManager::LayerManager()
{

}


jubeat_online::graphics::layer::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const bool isVSync,
	const unsigned int fpsLimit,
	const sf::Vector2i startWindowPosition,
	const sf::Uint32 style)
	: vmode(vmode),
	window_style(style),
	window_title(window_title),
	isVSync(isVSync),
	fpsLimit(fpsLimit),
	is_thread_running(new bool(false))
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
	
	this->window_position = startWindowPosition;
}





jubeat_online::graphics::layer::LayerManager::~LayerManager()
{
	//全てのレイヤーの解放
	for (auto p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		if ((*p).lb) {
			(*p).lb->Exit();
		}

		p = this->layer_list->erase(p);
	}

	//ウィンドウの終了
	this->window.close();
}


//#############  ウィンドウの生成  ###############

void jubeat_online::graphics::layer::LayerManager::createWindow(void)
{
	
	this->window.create(this->vmode, this->window_title, this->window_style);
	this->window.clear();

	this->window.setVerticalSyncEnabled(this->isVSync);
	this->window.setFramerateLimit(this->fpsLimit);
	this->window.setPosition(this->window_position);

	this->window_buffer.create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	this->window_buffer.clear();
	this->window_buffer.setSmooth(true);
}


//#############  レイヤーの追加  ###############

void jubeat_online::graphics::layer::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{

	//レイヤーの初期化
	layer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	layer->setSmooth(true);
	layer->Init();

	//初期化が完了してからDrawをはじめる

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

	//shared_ptrはスレッドセーフ
	this->layer_list->insert(p,newlb);

	
}

void jubeat_online::graphics::layer::LayerManager::run(void)
{
	std::thread th(&LayerManager::process, this);
	th.detach();	//スレッドの開始
}

bool jubeat_online::graphics::layer::LayerManager::isThreadRunning(void) const
{
	return *this->is_thread_running;
}


//#############  レイヤー描写フロー  ###############
void jubeat_online::graphics::layer::LayerManager::process(void)
{

	*this->is_thread_running = true;

	while (this->window.isOpen()) {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			//「クローズが要求された」イベント：ウインドウを閉じる
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) this->window.close();
		}


		this->window.clear();
		this->window_buffer.clear();

		if (this->layer_list->size() > 0) {
			for (auto p = --this->layer_list->end(); /*p != this->layer_list->end()*/; p--) {
				//描写
				p->lb->Draw();

				
				//終了検知
				if (p->lb->getExitCode() != 0) {
					//終了処理
					p->lb->Exit();
					//リストから削除
					//デクリメントだから全ループにおいてp--が可能
					p = this->layer_list->erase(p);
				}
				else {

					//画面更新
					p->lb->display();

					sf::Sprite sp(p->lb->getTexture());

					//ウィンドウバッファに描写
					this->window_buffer.draw(sp);
				}

				if (p == this->layer_list->begin()) break;	//全てのレイヤーを描写済み
			}
		}

		//ウィンドウバッファのアップデート
		this->window_buffer.display();

		//スプライトの作成
		sf::Sprite wsp(this->window_buffer.getTexture());

		//スプライトごにょごにょ
		sf::Vector2f scale;
		scale.x = static_cast<float>(this->window.getSize().x) / static_cast<float>(this->window_buffer.getSize().x);
		scale.y = static_cast<float>(this->window.getSize().y) / static_cast<float>(this->window_buffer.getSize().y);

		if (scale.x > scale.y) scale.x = scale.y;
		else scale.y = scale.x;

		wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
		wsp.setPosition(this->vmode.width / 2.0f, this->vmode.height / 2.0f);
		wsp.setScale(scale);
		
		//画面描写
		this->window.draw(wsp);

		//画面アップデート
		this->window.display();

	}


	for (auto p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		p->lb->Exit();
		p = this->layer_list->erase(p);
	}

	*this->is_thread_running = false;

}
