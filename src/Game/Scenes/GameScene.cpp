#include "GameScene.hpp"

//Layer include
#include "Game/Layers/BackgroundLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"
#include "Game/Layers/MusicInfoLayer.hpp"
#include "Game/Layers/SequencePlayer.hpp"
#include "Game/Layers/ShutterLayer.hpp"
#include "Game/Layers/RivalShutterLayer.hpp"
#include "Game/Layers/ScoreLayer.hpp"

//for panel position config
#include "Game/PanelPosition.hpp"

#include "Jmemo2/Parser.hpp"
#include "Jmemo2/YoubeatParser.hpp"

#include "Models/Configures.hpp"

//for sort
#include <algorithm>

//for panel input
#include "Input/Event.hpp"

//for debug
#include <iostream>


using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;
using namespace jubeon::input;

void jubeon::game::scenes::GameScene::init(void)
{

	this->music.reset(new Music("musics/demo_music/demo_music.json", "musics/demo_music"));
	this->music->load();
	music->setForPlay();

	//イベントのコールバックをこっちに変更
	this->gs_event.music = this->music.get();
	LayerManager::getInstance("mainwindow")->setCallback(std::bind(std::mem_fn(&EventBase::pollEvent), &this->gs_event, std::placeholders::_1));
	

	//パネルの設定を読み出す
	for (auto pp = this->panel_position.begin(); pp != this->panel_position.end(); pp++) pp->load();
	

	parser::YoubeatParser notes(jubeon::parser::YoubeatParser::loadFromFile("musics/demo_music/demo_music.txt"));






	//シーケンステスト
	//SAMB読んで見る
	//Jmemo2::Parser jmemo2;
	//jmemo2.initWithFileName("musics/SABM/SABM.jmemo2");
	
	//this->sequence.reset( new jubeon::parser::YoubeatParser(jubeon::parser::YoubeatParser::loadFromFile("musics/Daydream Cafe/note.ndt")));
	
	this->player.initForAuto(notes, 0);
	this->player1.initForPlay(this->gs_event.getPanelStreamBuf(), notes, -2000);

	//std::vector<Note> notes = jmemo2.getNotes();

	//std::sort(notes.begin(), notes.end(), [](Note x, Note y) -> int { return (x.getJustTime() < y.getJustTime()); });

	//*********シーケンステストここまで



	//TEMP
	///////////////////////
	// レイヤーの追加
	///////////////////////
	shared_ptr<layers::BackgroundLayer> bg(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo(new layers::MusicInfoLayer(music));
	shared_ptr<layers::ShutterLayer> shutterlayer(new layers::ShutterLayer);
	shared_ptr<layers::RivalShutterLayer> rival1(new layers::RivalShutterLayer(sf::Vector2f(this->panel_position[1].get(0).left, this->panel_position[1].get(0).top), this->music, BASIC));
	shared_ptr<layers::RivalShutterLayer> rival2(new layers::RivalShutterLayer(sf::Vector2f(288.0f, 122.0f), this->music, EXTREME));
	shared_ptr<layers::RivalShutterLayer> rival3(new layers::RivalShutterLayer(sf::Vector2f(546.0f, 122.0f)));
	shared_ptr<layers::SequencePlayer> sequenceplayer(new layers::SequencePlayer(this->player.getSequence(), this->music.get(), &this->player, &this->panel_position[0], 0));
	shared_ptr<layers::SequencePlayer> sequenceplayer2(new layers::SequencePlayer(this->player1.getSequence(), this->music.get(), &this->player1, &this->panel_position[1], 0));
	//shared_ptr<layers::SequencePlayer> sequenceplayer2(new layers::SequencePlayer(this->sequence, this->music, this->playrecord, sub_panel1_position, 0));
	shared_ptr<layers::ScoreLayer> scorelayer(new layers::ScoreLayer(&this->player, this->music.get()));
	shared_ptr<layers::PushframeLayer> push_frame_layer(new layers::PushframeLayer(&this->panel_position[0], this->gs_event.getPanelStreamBuf()));

    LayerManager * mainwindow = LayerManager::getInstance("mainwindow");
	mainwindow->addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	mainwindow->addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	mainwindow->addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(scorelayer, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(rival1, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(rival2, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(rival3, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(sequenceplayer, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(sequenceplayer2, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow->addLayer(push_frame_layer, LayerManager::MAIN, 0);



	//楽曲の再生

	//タイムマーカーを打つ


	music->playSound(0);

	
}

jubeon::game::scenes::GameScene::GameScene()
	: player("WHITE**"), player1("PLAYER1"),
	panel_position
		{PanelPosition("media/config/mainpanel.json"),
		PanelPosition("media/config/subpanel1.json"),
		PanelPosition("media/config/subpanel2.json"),
		PanelPosition("media/config/subpanel3.json")}
{
}

int jubeon::game::scenes::GameScene::process(void)
{

	

	player.updateInput(this->music.get());

	return 0;
}

strbuf::StreamBuffer<jubeon::input::PanelInput>* jubeon::game::scenes::EventBase::getPanelStreamBuf(void)
{
	return &this->pinput_sb;
}

jubeon::game::scenes::EventBase::EventBase()
	: pinput_que(new strbuf::InputStream<input::PanelInput>())
{
	this->pinput_sb.addInputStream(this->pinput_que);
}


void jubeon::game::scenes::EventBase::pollEvent(sf::Event e)
{
	//Select Input data

	if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
		for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
			if (models::Configures::getInstance()->panel_config->getHidID(pidx) == -1) {
				if (models::Configures::getInstance()->panel_config->getKeyCode(pidx) == e.key.code) {
					//getPlayingCurrentTime is const function so this is thread safe.
					this->pinput_que->que(input::PanelInput(pidx, (e.type == sf::Event::KeyPressed ? PUSH : RELEASE), music->getPlayingCurrentTime()));
					this->pinput_sb.flush();
					break;
				}
			}
		}
	}
	else if (e.type == sf::Event::JoystickButtonPressed || e.type == sf::Event::JoystickButtonReleased) {
		for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
			if (models::Configures::getInstance()->panel_config->getHidID(pidx) == e.joystickButton.joystickId) {
				if (models::Configures::getInstance()->panel_config->getJoystickCode(pidx) == e.joystickButton.button) {
					this->pinput_que->que(input::PanelInput(pidx, (e.type == sf::Event::JoystickButtonPressed ? PUSH : RELEASE), music->getPlayingCurrentTime()));
					this->pinput_sb.flush();
					break;
				}
			}
		}
	}
	this->pinput_sb.flush();
}

