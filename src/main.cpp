#include <memory>


#include "Graphics/Layer/LayerManager.hpp"

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
using namespace std;

int main(int argc, char * argv[]) {

#ifdef _DEBUG
	//メモリリークのログを出力してくれるらしい
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	jubeon::systems::Logger::information("jubeonが起動しました");
	
	jubeon::graphics::LayerManager mainwindow("test", sf::VideoMode(1080, 1920), false, 0, sf::Vector2i(1920, -840), sf::Style::None);
	
	shared_ptr<layers::BackgroundLayer> bg			(new layers::BackgroundLayer);
	shared_ptr<layers::FrameLayer> frame			(new layers::FrameLayer);
	shared_ptr<layers::MusicInfoLayer> musicinfo	(new layers::MusicInfoLayer);
	shared_ptr<layers::ShutterLayer> shutterlayer	(new layers::ShutterLayer);
	
	vector<Note> hoge;
	//shared_ptr<Sequence> sequence(new Sequence(hoge));
	
	Music mus;

	//まずmusicに何か指定
	//ここはアクセサを介した実装へ
	mus.soundbuffer.loadFromFile("media/demo.flac");
	mus.soundplayer.setBuffer(mus.soundbuffer);

	//このデータをいじって、あらかじめjudgedに入れておけば自動プレイ（リプレイ）が可能
	//std::unique_ptr<jubeon::game::PlayRecord> playrecord(new jubeon::game::PlayRecord);
	
	/*PlayRecord::NoJudgedList pi_list(new std::list<PanelInput>());
	PanelInput tmp;
	tmp.j = jubeon::game::NOJUDGE;

	for (int i = 0; i < 15; i++) {
		tmp.ms = i * 4000; tmp.panel_no = 1; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 2; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 5; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 7; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 8; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 9; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 12; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000; tmp.panel_no = 13; tmp.t = PanelEvent::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 1; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 2; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 5; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 7; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 8; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 9; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 12; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = i * 4000 + 2000; tmp.panel_no = 13; tmp.t = PanelEvent::RELEASE;
		pi_list->push_back(tmp);
	}
	
	playrecord->setJudgedList(std::move(pi_list));*/

	//?
	//shared_ptr<layers::SequencePlayer> seqplayer(new layers::SequencePlayer(sequence, &mus, std::move(playrecord)));


	mainwindow.addLayer(bg, jubeon::graphics::LayerManager::BACKGROUND, 0);
	mainwindow.addLayer(frame, jubeon::graphics::LayerManager::FOREGROUND, 0);
	mainwindow.addLayer(musicinfo, jubeon::graphics::LayerManager::MAIN, 0);
	mainwindow.addLayer(shutterlayer, jubeon::graphics::LayerManager::MAIN, 0);
	//mainwindow.addLayer(seqplayer, jubeon::graphics::LayerManager::MAIN, 0);	//上に追加。番号は重複しても全然問題ない。
	
	mus.startToPlay();

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