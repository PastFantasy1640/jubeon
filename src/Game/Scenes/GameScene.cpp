#include "GameScene.hpp"

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



using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;
using namespace jubeon::input;

int jubeon::game::scenes::GameScene::process(void)
{
	//TEMP
	shared_ptr<layers::BackgroundLayer> bg			(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame			(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo	(new layers::MusicInfoLayer);
	shared_ptr<layers::ShutterLayer> shutterlayer	(new layers::ShutterLayer);
	
	
	vector<Note> hoge;

	std::shared_ptr<Music> music = Music::load("musics/testmuisic/testmusic.json");



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


	this->getMainWindow()->addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	this->getMainWindow()->addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	this->getMainWindow()->addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);

	music->setForPlay();

	music->playSound();


	//シーケンステスト
	std::vector<Note> notes, notes_sort;
	for (int i = 0; i < 50; i++) {
		notes.push_back(Note(500 + 4000 * i, 1));
		notes.push_back(Note(2000 + 4000 * i, 4));
		notes.push_back(Note(1000 + 4000 * i, 2));
		notes.push_back(Note(3500 + 4000 * i, 7));
		notes.push_back(Note(3500 + 4000 * i, 11));
		notes.push_back(Note(1500 + 4000 * i, 3));
		notes.push_back(Note(3000 + 4000 * i, 6));
		notes.push_back(Note(2500 + 4000 * i, 5));
		notes.push_back(Note(0 + 4000 * i, 0));
	}

	notes_sort = notes;

	//ソートしてみる
	int ms = 0;/*
	for (auto p : notes) {
		if (ms > p.getJustTime()) std::cout << "eeeeeeeeeeeeeerorr" << std::endl;	//ソートできてない
		ms = p.getJustTime();
	}*/

	Sequence sequence(notes);
	//シーケンステストここまで

	while (this->getMainWindow()->isWindowOpening()) {
		sf::Event e;
		while (this->getMainWindow()->getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) this->getMainWindow()->closeWindow();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}



	return 1;	//ソフト終了
}
