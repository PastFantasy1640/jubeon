
//shared_ptr, unique_ptr
#include <memory>

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"

//Logger
#include "Systems/Logger.hpp"


#include "Game/Layers/BackgroundLayer.hpp"



#ifdef _DEBUG
#include <crtdbg.h>	//メモリリークログ用
#endif

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;

int main(int argc, char * argv[]) {

#ifdef _DEBUG
	//メモリリークのログを出力してくれるらしい
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//起動時のログ
	Logger::information("jubeonが起動しました");
	
	//メインウィンドウのインスタンスを生成
	//TO DO : 設定ファイルからの読み出し
	LayerManager mainwindow("jubeon v0.1", sf::VideoMode(1080, 1920), false, 0, sf::Vector2i(1920, -840), sf::Style::None);
	
	//最初に使用するシーンを生成
	unique_ptr<scenes::GameScene> upGameSceneInstance(new scenes::GameScene());

	//ウィンドウの生成
	mainwindow.run();

	//シーン処理開始
	//int ret = Scene::process(&mainwindow, std::move(upGameSceneInstance));
	shared_ptr<layers::BackgroundLayer> bg(new layers::BackgroundLayer);
	mainwindow.addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	while (mainwindow.isWindowOpening()) {
		sf::Event e;
		while (mainwindow.getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) mainwindow.closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) mainwindow.closeWindow();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	//システム終了
	//return ret;

}