
//shared_ptr, unique_ptr
#include <memory>

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"

//Layer include
#include "Game/Layers/BackgroundLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"
#include "Game/Layers/MusicInfoLayer.hpp"
#include "Game/Layers/SequencePlayer.hpp"
#include "Game/Layers/ShutterLayer.hpp"

//for test
#include "Game/Sequence.hpp"
#include "Game/Music.hpp"
#include "Game/PlayRecord.hpp"


#include "Systems/Logger.hpp"

#ifdef _DEBUG
#include <crtdbg.h>	//メモリリークログ用
#endif

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::input;
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
	unique_ptr<scenes::GameScene> upGameSceneInstance;

	Scene::process(&mainwindow, std::move(upGameSceneInstance));

	/*
	shared_ptr<layers::BackgroundLayer> bg			(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame			(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo	(new layers::MusicInfoLayer);
	shared_ptr<layers::ShutterLayer> shutterlayer	(new layers::ShutterLayer);
	*/


	vector<Note> hoge;
	
	Music mus;

	//まずmusicに何か指定
	//ここはアクセサを介した実装へ
	mus.soundbuffer.loadFromFile("media/demo.flac");
	mus.soundplayer.setBuffer(mus.soundbuffer);

	//このデータをいじって、あらかじめjudgedに入れておけば自動プレイ（リプレイ）が可能
	std::unique_ptr<jubeon::game::PlayRecord> playrecord(new jubeon::game::PlayRecord);
	
	PanelInput p;

	for (int i = 0; i < 15; i++) {
		playrecord->addJudged(PanelInput(2, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(5, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(7, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(8, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(9, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(12, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(13, PUSH, i * 4000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(2, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(5, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(7, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(8, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(9, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(12, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		playrecord->addJudged(PanelInput(13, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
	}


	//?
	//shared_ptr<layers::SequencePlayer> seqplayer(new layers::SequencePlayer(sequence, &mus, std::move(playrecord)));



	mainwindow.addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	mainwindow.addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	mainwindow.addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow.addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);
	
	mus.startToPlay();



	jubeon::systems::Scene::process(;

	mainwindow.run();

	while (mainwindow.isWindowOpening()) {
		sf::Event e;
		while (mainwindow.getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) mainwindow.closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) mainwindow.closeWindow();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	

	return 0;
}