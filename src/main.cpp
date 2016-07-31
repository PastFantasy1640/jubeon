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

using namespace jubeat_online;

int main(int argc, char * argv[]) {

#ifdef _DEBUG
	//メモリリークのログを出力してくれるらしい
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	jubeat_online::systems::Logger::information("jubeonが起動しました");


	

	jubeat_online::graphics::layer::LayerManager a("test", sf::VideoMode(1080, 1920), false, 0, sf::Vector2i(1920, -840), sf::Style::None);

	a.createWindow();

	std::shared_ptr<game::layers::BackgroundLayer> bg(new game::layers::BackgroundLayer);
	std::shared_ptr<game::layers::FrameLayer> frame(new game::layers::FrameLayer);
	std::shared_ptr<game::layers::MusicInfoLayer> musicinfo(new game::layers::MusicInfoLayer);
	std::shared_ptr<game::layers::ShutterLayer> shutterlayer(new game::layers::ShutterLayer);
	
	game::Sequence seq("hogehoge");
	game::Music mus;

	//まずmusicに何か指定
	//ここはアクセサを介した実装へ
	mus.soundbuffer.loadFromFile("media/demo.flac");
	mus.soundplayer.setBuffer(mus.soundbuffer);

	//このデータをいじって、あらかじめjudgedに入れておけば自動プレイ（リプレイ）が可能
	std::unique_ptr<game::PlayRecord> playrecord(new jubeat_online::game::PlayRecord);
	
	std::unique_ptr<std::list<game::PlayRecord::PanelInput>> pi_list(new std::list<game::PlayRecord::PanelInput>());
	game::PlayRecord::PanelInput tmp;
	tmp.j = jubeat_online::game::NOJUDGE;

	for (int i = 0; i < 10; i++) {
		tmp.ms = 4000 + i * 4000; tmp.panel_no = 0; tmp.t = game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 5000 + i * 4000; tmp.panel_no = 4; tmp.t = game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 6000 + i * 4000; tmp.panel_no = 8; tmp.t = game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 6500 + i * 4000; tmp.panel_no = 9; tmp.t = game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 7000 + i * 4000; tmp.panel_no = 12; tmp.t = game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 4500 + i * 4000; tmp.panel_no = 0; tmp.t = game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 5500 + i * 4000; tmp.panel_no = 4; tmp.t = game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 8; tmp.t = game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 9; tmp.t = game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 12; tmp.t = game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
	}
	
	playrecord->setJudgedList(std::move(pi_list));


	std::shared_ptr<game::layers::SequencePlayer> seqplayer(new game::layers::SequencePlayer(&seq, &mus, std::move(playrecord)));


	a.addLayer(bg, jubeat_online::graphics::layer::LayerManager::BACKGROUND, 0);
	a.addLayer(frame, jubeat_online::graphics::layer::LayerManager::FOREGROUND, 0);
	a.addLayer(musicinfo, jubeat_online::graphics::layer::LayerManager::MAIN, 0);
	a.addLayer(shutterlayer, jubeat_online::graphics::layer::LayerManager::MAIN, 0);
	a.addLayer(seqplayer, jubeat_online::graphics::layer::LayerManager::MAIN, 0);	//上に追加。番号は重複しても全然問題ない。
	
	mus.startToPlay();

	a.process();

	return 0;
}