#include "GameScene.hpp"

//Layer include
#include "Game/Layers/BackgroundLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"
#include "Game/Layers/MusicInfoLayer.hpp"
#include "Game/Layers/SequencePlayer.hpp"
#include "Game/Layers/ShutterLayer.hpp"
#include "Game/Layers/RivalShutterLayer.hpp"

//for panel position config
#include "Game/PanelPosition.hpp"

#include "Jmemo2/Parser.hpp"

//for sort
#include <algorithm>

//for panel input
#include "Input/ListenPanel.hpp"

//for debug
#include <iostream>

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;
using namespace jubeon::input;

void jubeon::game::scenes::GameScene::init(void)
{

	this->music = Music::load("musics/SABM/SABM.json");

	//パネルの設定を読み出す
	shared_ptr<PanelPosition> main_panel_position(new PanelPosition);
	main_panel_position->loadJson("media/config/mainpanel.json");
	shared_ptr<PanelPosition> sub_panel1_position(new PanelPosition);
	sub_panel1_position->loadJson("media/config/subpanel1.json");
	
	vector<Note> hoge;

	this->offset = -430;


	//このデータをいじって、あらかじめjudgedに入れておけば自動プレイ（リプレイ）が可能
	this->playrecord.reset(new jubeon::game::PlayRecord);
	/*
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
	}*/

	//this->playrecord->readFromFile("hogehogehoge1.txt");





	//シーケンステスト
	//SAMB読んで見る
	Jmemo2::Parser jmemo2;
	jmemo2.initWithFileName("musics/SABM/SABM.jmemo2");

	std::vector<Note> notes = jmemo2.getNotes();

	std::sort(notes.begin(), notes.end(), [](Note x, Note y) -> int { return (x.getJustTime() < y.getJustTime()); });

	//*********シーケンステストここまで

	//ファイルを読み込んでセット
	this->sequence.reset(new Sequence(notes));


	//TEMP
	///////////////////////
	// レイヤーの追加
	///////////////////////
	shared_ptr<layers::BackgroundLayer> bg(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo(new layers::MusicInfoLayer(music));
	shared_ptr<layers::ShutterLayer> shutterlayer(new layers::ShutterLayer);
	shared_ptr<layers::RivalShutterLayer> rival1(new layers::RivalShutterLayer(sf::Vector2f(30.0f, 122.0f), this->music, BASIC));
	shared_ptr<layers::RivalShutterLayer> rival2(new layers::RivalShutterLayer(sf::Vector2f(288.0f, 122.0f), this->music, EXTREME));
	shared_ptr<layers::RivalShutterLayer> rival3(new layers::RivalShutterLayer(sf::Vector2f(546.0f, 122.0f)));
	shared_ptr<layers::SequencePlayer> sequenceplayer(new layers::SequencePlayer(this->sequence, this->music, this->playrecord, main_panel_position, this->offset));
	shared_ptr<layers::SequencePlayer> sequenceplayer2(new layers::SequencePlayer(this->sequence, this->music, this->playrecord, sub_panel1_position, 0));

	this->push_frame_layer.reset(new layers::PushframeLayer(main_panel_position, music, this->playrecord));	//リプレイモード
//	this->push_frame_layer.reset(new layers::PushframeLayer(main_panel_position, music));	//再生モード

	this->getMainWindow()->addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	this->getMainWindow()->addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	this->getMainWindow()->addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(rival1, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(rival2, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(rival3, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(sequenceplayer, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(sequenceplayer2, jubeon::graphics::LayerManager::MAIN, 0);
	this->getMainWindow()->addLayer(this->push_frame_layer, LayerManager::MAIN, 0);



	//楽曲の再生
	//パネルのキューを全リセット
	ListenPanel::getEvent();

	//タイムマーカーを打つ
	ListenPanel::setTime(-2300);

	music->setForPlay();

	music->playSound(2000);
		
}

int jubeon::game::scenes::GameScene::process(void)
{
	//イベントの処理
	sf::Event e;
	while (this->getMainWindow()->getWindowEvent(e)) {
		if (e.type == sf::Event::Closed) {
			return 1;
		}
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			this->playrecord->writeToFile("hogehogehoge2.txt");
			return 1;
		}
	}


	//パネルから入力を取ってくる
	std::vector<PanelInput> panelinput(ListenPanel::getEvent());

	//パネルから入力があったから、その処理を行う
	if (panelinput.size() > 0) this->processPanel(panelinput);


	return 0;
}


//パネルの処理
void jubeon::game::scenes::GameScene::processPanel(const std::vector<PanelInput> & pinput)
{
	for (auto ite : pinput) {

		//枠レイヤーに描写
		if (ite.t) this->push_frame_layer->setPushing(ite.panel_no);
		else {
			this->push_frame_layer->setReleasing(ite.panel_no);
		}

		//判定
		if (ite.t) {
			const jMillisec now = ite.ms - this->offset;
			const auto p = this->sequence->search(now + JudgeSize::B_POOR);

			size_t distance = std::distance(this->sequence->begin(), p);

			Judge j(NOJUDGE);
			auto ptemp = p;

			//判定範囲内にあるノーツを端っこから検査
			for (; ptemp != this->sequence->end(); ptemp++, distance++) {
				if (ptemp->getJustTime() >= now + JudgeSize::A_POOR) break;	//範囲外なので該当するノーツはなかった。
				if (ptemp->getPanelIndex() == ite.panel_no && this->playrecord->seq_pr_mapping->count(distance) == 0) {
					//同じパネルで、未判定なノーツ
					if (ptemp->getJustTime() + JudgeSize::B_PERFECT <= now && now <= ptemp->getJustTime() + JudgeSize::A_PERFECT) j = PERFECT;
					else if (ptemp->getJustTime() + JudgeSize::B_GREAT <= now && now <= ptemp->getJustTime() + JudgeSize::A_GREAT) j = GREAT;
					else if (ptemp->getJustTime() + JudgeSize::B_GOOD <= now && now <= ptemp->getJustTime() + JudgeSize::A_GOOD) j = GOOD;
					else if (ptemp->getJustTime() + JudgeSize::B_POOR <= now && now < ptemp->getJustTime() + JudgeSize::B_GOOD) j = EARLY;
					else if (ptemp->getJustTime() + JudgeSize::A_GOOD < now && now <= ptemp->getJustTime() + JudgeSize::A_POOR) j = LATE;
					//順当に行けばここはかならずjに代入されているはずだが
					if (j != NOJUDGE) {
						(*this->playrecord->seq_pr_mapping)[distance] = playrecord->getJudgedList()->size();
						break;
					}
				}
			}

			playrecord->addJudged(ite, j);

		}
		else {
			playrecord->addJudged(ite, NOJUDGE);
		}
	}
}
