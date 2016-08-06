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

void jubeon::game::scenes::GameScene::init() {
	if (!this->isinited) {
		shared_ptr<layers::BackgroundLayer> bg(new layers::BackgroundLayer);
		shared_ptr<layers::FrameLayer> frame(new layers::FrameLayer);
		shared_ptr<layers::MusicInfoLayer> musicinfo(new layers::MusicInfoLayer);
		shared_ptr<layers::ShutterLayer> shutterlayer(new layers::ShutterLayer);


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


		this->getMainWindow()->addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
		this->getMainWindow()->addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
		this->getMainWindow()->addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
		this->getMainWindow()->addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);

		mus.startToPlay();

		this->isinited = true;

	
	}
}

int jubeon::game::scenes::GameScene::process(void)
{

	if (!this->isinited) this->init();

	sf::Event e;
	while (this->getMainWindow()->getWindowEvent(e)) {
		if (e.type == sf::Event::Closed) {
			return 1;
		}
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			return 1;
		}
	}

	std::this_thread::sleep_for(std::chrono::microseconds(1));

	return 0;	//ソフト終了
}
