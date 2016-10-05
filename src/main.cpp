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
#include "Models/Configures.hpp"
#include "Storages/JsonFileStorage.hpp"

//shared_ptr
#include <memory>

////////////////////////////////////////////////////////
//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"


//for config loading
#include "Models/PanelConfig.hpp"

//for panel input
#include "Input/Event.hpp"

#include <thread>

//for linux (multi thread)
#ifndef _MBCS
#include <X11/Xlib.h>
#endif

//for debugging (memory reak)
#if defined(_DEBUG) && defined(_MBCS)
#include <crtdbg.h>
#endif

using namespace jubeon::game;
using namespace jubeon::models;
using namespace jubeon::storages;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;


int main(int argc, char * argv[]){

#ifndef _MBCS
	//in LINUX, call this to be able to use multithread.
	XInitThreads();
#endif

    //Starting Log
    Logger::information("Starting jubeon program.");

#ifdef _DEBUG
    Logger::information("[DEBUG]Debug mode is available.");
#ifdef _MBCS
	//in debug mode and vs compiler, output the log leaked memories.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::information("[DEBUG]Output the log leaked memories.");
#endif
#endif


	///////////////////////////////////////////////////////////
    // main window create
    ///////////////////////////////////////////////////////////
    //Load config
    Logger::information("Loading window layout.");
    Configures::getInstance()->window_config = JsonFileStorage("media/config/window_layout.json").getModel<WindowConfig>();

    //create window
    LayerManager mainwindow("mainwindow");

	//
    
    mainwindow.create(
        sf::VideoMode(
            static_cast<unsigned int>(Configures::getInstance()->window_config->getSize().x),
            static_cast<unsigned int>(Configures::getInstance()->window_config->getSize().y)),
        "jubeon v0.1",              //window title
        sf::Style::None);
        
    mainwindow.setPosition(
        sf::Vector2i(
            static_cast<int>(Configures::getInstance()->window_config->getPosition().x),
            static_cast<int>(Configures::getInstance()->window_config->getPosition().y))
        );
        
    mainwindow.setVerticalSyncEnabled(Configures::getInstance()->window_config->getVsyncEnabled());
    if(!Configures::getInstance()->window_config->getVsyncEnabled()) mainwindow.setFramerateLimit(80);
    mainwindow.setActive(false);
    
    //Finished creating the window.
    Logger::information("Finished creating the window.");



/////////////////////////////////////////

	//パネルコンフィグ
	jubeon::storages::JsonFileStorage keyconfig_storage("media/config/keyconfig.json");
	shared_ptr<jubeon::models::PanelConfig> pconfig = keyconfig_storage.getModel<jubeon::models::PanelConfig>();

	pconfig->setInstance(pconfig);	//シングルトン？

////////////////////////////////////////
	
	
	//Start Scene
	int ret = Scene::process<scenes::GameScene>(&mainwindow);
	
	
	//イベント監視
	jubeon::input::Event::getInstance(&mainwindow)->process(&mainwindow);

	//現在起動中のウィンドウを終了し、レイヤーを全部解放
	mainwindow.closeWindow();

	//システム終了
	return ret;
}


