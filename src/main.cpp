/////////////////////////////////////////////////////////////////////////////
//    jubeon   - (c) 2016 jubeon project
//
//        white   musou1500   hermit   retasu
//
//
//    main.cpp  - (c) 2016 white
/////////////////////////////////////////////////////////////////////////////

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Logger
#include "Systems/Logger.hpp"

//Window Config
#include "Models/WindowConfig.hpp"
#include "Storages/JsonFileStorage.hpp"

//shared_ptr
#include <memory>

////////////////////////////////////////////////////////
//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"


//test scene
#include "Game/Scenes/TemplateScene.hpp"



//for config loading
#include "Models/PanelConfig.hpp"

//for panel input
#include "Input/ListenPanel.hpp"


#if defined(_DEBUG) && defined(_MSVC)
#include <crtdbg.h>
#endif

using namespace jubeon::game;
using namespace jubeon::models;
using namespace jubeon::storages;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;

int main(int argc, char * argv[]){

    //Starting Log
    Logger::information("Starting jubeon program.");

#ifdef _DEBUG
    Logger::information("[DEBUG]Debug mode is available.");

#ifdef _MSVC
	//in debug mode and vs compiler, output the log leaked memories.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::information("[DEBUG]Output the log leaked memories.");
#endif
#endif

    //////////////////////////
    // main window create
    //////////////////////////
    //Load config
    Logger::information("Loading window layout.");
    shared_ptr<WindowConfig> window_config = JsonFileStorage("media/config/window_layout.json").getModel<WindowConfig>();
    
    //setting window
    LayerManager mainwindow(
        "jubeon v0.1",              //window title
        sf::VideoMode(
            static_cast<unsigned int>(window_config->getSize().x),
            static_cast<unsigned int>(window_config->getSize().y)),
        window_config->getVsyncEnabled(),
        80,
        sf::Vector2i(
            static_cast<int>(window_config->getPosition().x),
            static_cast<int>(window_config->getPosition().y)),
        sf::Style::None);
    
    //Create Window
	mainwindow.createWindow();
    
    //Finished creating the window.
    Logger::information("Finished creating the window.");



/////////////////////////////////////////

	//パネルコンフィグ
	//jubeon::storages::JsonFileStorage keyconfig_storage("media/config/keyconfig.json");
	//shared_ptr<jubeon::models::PanelConfig> pconfig = keyconfig_storage.getModel<jubeon::models::PanelConfig>();

	//pconfig->setInstance(pconfig);	//シングルトン？

	//パネル起動
	//jubeon::input::ListenPanel::Listen();

	//最初に使用するシーンを生成
	shared_ptr<scenes::GameScene> upSceneInstance(new scenes::GameScene());

	int ret = Scene::process(&mainwindow, upSceneInstance);

	//パネルの終了
	//jubeon::input::ListenPanel::Close();

	//現在起動中のウィンドウを終了し、レイヤーを全部解放
	mainwindow.closeWindow();

	//システム終了
	return ret;
}


