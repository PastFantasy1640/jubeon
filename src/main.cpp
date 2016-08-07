
//shared_ptr, unique_ptr
#include <memory>

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"

#include "Storages/JsonFileStorage.hpp"
#include "Models/WindowConfig.hpp"


//Logger
#include "Systems/Logger.hpp"

//for config loading
#include "Storages/JsonFileStorage.hpp"
#include "Models/PanelConfig.hpp"

//for panel input
#include "Input/ListenPanel.hpp"


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
	LayerManager mainwindow("jubeon v0.1", sf::VideoMode(1080, 1920), true, 80, sf::Vector2i(1920, -840), sf::Style::None);

	//メインウィンドウの生成
	mainwindow.createWindow();


	//パネルコンフィグ
	jubeon::storages::JsonFileStorage keyconfig_storage("media/config/keyconfig.json");
	shared_ptr<jubeon::models::PanelConfig> pconfig = keyconfig_storage.getModel<jubeon::models::PanelConfig>();

	pconfig->setInstance(pconfig);	//シングルトン？

	//パネル起動
	jubeon::input::ListenPanel::Listen();

	//最初に使用するシーンを生成
	unique_ptr<scenes::GameScene> upGameSceneInstance(new scenes::GameScene());
	
	int ret = Scene::process(&mainwindow, std::move(upGameSceneInstance));

	//現在起動中のウィンドウを終了し、レイヤーを全部解放
	mainwindow.closeWindow();

	//システム終了
	return ret;

}
