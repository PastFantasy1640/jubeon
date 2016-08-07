#include "GameScene.hpp"

//Layer include
#include "Game/Layers/BackgroundLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"
#include "Game/Layers/MusicInfoLayer.hpp"
#include "Game/Layers/SequencePlayer.hpp"
#include "Game/Layers/ShutterLayer.hpp"

//for panel position config
#include "Game/PanelPosition.hpp"

//for sort
#include <algorithm>

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;
using namespace jubeon::input;

void jubeon::game::scenes::GameScene::init(void)
{
	//TEMP
	shared_ptr<layers::BackgroundLayer> bg(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo(new layers::MusicInfoLayer);
	shared_ptr<layers::ShutterLayer> shutterlayer(new layers::ShutterLayer);

	this->getMainWindow()->addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	this->getMainWindow()->addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	this->getMainWindow()->addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);

	//パネルの設定を読み出す
	shared_ptr<PanelPosition> main_panel_position(new PanelPosition);
	main_panel_position->loadJson("media/config/mainpanel.json");
	shared_ptr<PanelPosition> sub_panel1_position(new PanelPosition);
	sub_panel1_position->loadJson("media/config/subpanel1.json");

	//マッピングの用意
	this->seq_pr_mapping.reset(new std::map<const Note *, const JudgedPanelInput *>);

	vector<Note> hoge;

	this->music = Music::load("musics/testmuisic/testmusic.json");



	//このデータをいじって、あらかじめjudgedに入れておけば自動プレイ（リプレイ）が可能
	this->playrecord.reset(new jubeon::game::PlayRecord);
	
	for (int i = 0; i < 15; i++) {
		this->playrecord->addJudged(PanelInput(2, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(1, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(5, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(7, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(8, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(9, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(12, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(13, PUSH, i * 4000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(2, RELEASE, i * 4000 + 50), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(1, RELEASE, i * 4000 + 100), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(5, RELEASE, i * 4000 + 200), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(7, RELEASE, i * 4000 + 500), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(8, RELEASE, i * 4000 + 1000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(9, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(12, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
		this->playrecord->addJudged(PanelInput(13, RELEASE, i * 4000 + 2000), Judge::NOJUDGE);
	}






	//シーケンステスト
	std::vector<Note> notes;
	for (int i = 1; i < 50; i++) {
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

	std::sort(notes.begin(), notes.end(), [](Note x, Note y) -> int { return (x.getJustTime() < y.getJustTime()); });

	//*********シーケンステストここまで

	//ファイルを読み込んでセット
	this->sequence.reset(new Sequence(notes));

	shared_ptr<layers::SequencePlayer> sequenceplayer(new layers::SequencePlayer(this->sequence, this->music, this->playrecord, this->seq_pr_mapping, main_panel_position));
	shared_ptr<layers::SequencePlayer> sequenceplayer2(new layers::SequencePlayer(this->sequence, this->music, this->playrecord, this->seq_pr_mapping, sub_panel1_position));
	this->getMainWindow()->addLayer(sequenceplayer, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(sequenceplayer2, jubeon::graphics::LayerManager::MAIN, 0);


	//楽曲の再生
	music->setForPlay();

	music->playSound();

	this->isinited = true;
	
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


	return 0;
}
