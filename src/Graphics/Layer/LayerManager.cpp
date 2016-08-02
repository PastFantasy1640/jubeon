/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "LayerBase.hpp"

#include <thread>

#include "../../Systems/Exceptions.hpp"



using namespace jubeon::graphics;

const sf::Vector2u jubeon::graphics::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768, 1360);

//コンストラクタ
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
	is_thread_running(new bool(false)),
	is_open_window(new bool(false))
{
}

//デストラクタ
jubeon::graphics::LayerManager::~LayerManager()
{
	//あえてリリースする必要は無い？
}

//レイヤーの追加
void jubeon::graphics::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{
	//まずレイヤーの初期化を行う。
	layer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	layer->setSmooth(true);
	layer->Init();

	{
		//レイヤーの追加
		//以下はlayer_listに対してロックを掛けた状態で実行される
		//分かりやすいようにスコープを分ける
		std::lock_guard<std::mutex> lock(this->layer_list_mtx);

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
}

//スレッドの開始
void jubeon::graphics::LayerManager::run(void)
{
	//まずウィンドウを生成
	this->window.reset(new sf::RenderWindow(this->vmode, this->window_title, this->window_style));
	this->window->clear();

	this->window->setVerticalSyncEnabled(this->isVSync);
	this->window->setFramerateLimit(this->fpsLimit);
	this->window->setPosition(this->window_position);

	//次にウィンドウバッファの生成
	this->window_buffer.reset(new sf::RenderTexture());
	this->window_buffer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	this->window_buffer->clear();
	this->window_buffer->setSmooth(true);

	//スレッドの生成
	*this->is_thread_running = true;
	*this->is_open_window = true;
	std::thread th(&LayerManager::process, this);
	th.detach();	//スレッドの開始
}

//ウィンドウが開いているか
bool jubeon::graphics::LayerManager::isWindowOpening(void) const
{
	return *this->is_thread_running;
}

//ウィンドウを終了させる
void jubeon::graphics::LayerManager::closeWindow(void)
{
	*this->is_open_window = false;
	while(*this->is_thread_running) std::this_thread::sleep_for(std::chrono::microseconds(1000));	//1ms待って問い合わせ（ロッキング）
}

bool jubeon::graphics::LayerManager::getWindowEvent(sf::Event & e)
{
	return this->window->pollEvent(e);
}

//レイヤー描写
void jubeon::graphics::LayerManager::process(void)
{
	//ループ開始
	while (this->window->isOpen()) {
	
		//スレッド終了検知
		if (*this->is_open_window == false) {
			this->window->close();
			*this->is_open_window = false;
			break;	//終了へ
		}

		this->window->clear();
		this->window_buffer->clear();

		if (this->layer_list.size() > 0) {
			for (auto p = --this->layer_list.end(); ; p--) {
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

					//sf::Sprite sp(p->lb->getTexture());

					//ウィンドウバッファに描写
					this->window_buffer->draw(sf::Sprite((*p)->getTexture()));
				}

				if (p == this->layer_list.begin()) break;	//全てのレイヤーを描写済み
			}
		}

		//ウィンドウバッファのアップデート
		this->window_buffer->display();

		//スプライトの作成
		sf::Sprite wsp(this->window_buffer->getTexture());

		//スプライトごにょごにょ
		sf::Vector2f scale;
		scale.x = static_cast<float>(this->window->getSize().x) / static_cast<float>(this->window_buffer->getSize().x);
		scale.y = static_cast<float>(this->window->getSize().y) / static_cast<float>(this->window_buffer->getSize().y);

		if (scale.x > scale.y) scale.x = scale.y;
		else scale.y = scale.x;

		wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
		wsp.setPosition(this->vmode.width / 2.0f, this->vmode.height / 2.0f);
		wsp.setScale(scale);
		
		//画面描写
		this->window->draw(wsp);

		//画面アップデート
		this->window->display();

	}

	//残ってるものすべて削除
	for (auto p = this->layer_list.begin(); p != this->layer_list.end(); ) {
		(*p)->Exit();
		p = this->layer_list.erase(p);
	}

	//スレッドの終了
	*this->is_thread_running = false;

}

