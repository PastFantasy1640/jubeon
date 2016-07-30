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
#include <crtdbg.h>	//���������[�N���O�p
#endif

int main(int argc, char * argv[]) {

#ifdef _DEBUG
	//���������[�N�̃��O���o�͂��Ă����炵��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	jubeat_online::systems::Logger::information("jubeat online���N�����܂���");


	jubeat_online::graphics::layer::LayerManager a("test",sf::VideoMode(768,1360),sf::Style::None);

	a.createWindow();
	a.setScale(1.41);

	jubeat_online::game::layers::BackgroundLayer bg;
	jubeat_online::game::layers::FrameLayer frame;
	jubeat_online::game::layers::MusicInfoLayer musicinfo;
	jubeat_online::game::layers::ShutterLayer shutterlayer;
	
	jubeat_online::game::Sequence seq("hogehoge");
	jubeat_online::game::Music mus;

	//�܂�music�ɉ����w��
	//�����̓A�N�Z�T�����������
	mus.soundbuffer.loadFromFile("media/demo.flac");
	mus.soundplayer.setBuffer(mus.soundbuffer);

	//���̃f�[�^���������āA���炩����judged�ɓ���Ă����Ύ����v���C�i���v���C�j���\
	std::unique_ptr<jubeat_online::game::PlayRecord> playrecord(new jubeat_online::game::PlayRecord);
	
	std::unique_ptr<std::list<jubeat_online::game::PlayRecord::PanelInput>> pi_list(new std::list<jubeat_online::game::PlayRecord::PanelInput>());
	jubeat_online::game::PlayRecord::PanelInput tmp;
	tmp.j = jubeat_online::game::NOJUDGE;

	for (int i = 0; i < 10; i++) {
		tmp.ms = 4000 + i * 4000; tmp.panel_no = 0; tmp.t = jubeat_online::game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 5000 + i * 4000; tmp.panel_no = 4; tmp.t = jubeat_online::game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 6000 + i * 4000; tmp.panel_no = 8; tmp.t = jubeat_online::game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 6500 + i * 4000; tmp.panel_no = 9; tmp.t = jubeat_online::game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 7000 + i * 4000; tmp.panel_no = 12; tmp.t = jubeat_online::game::PlayRecord::PUSH;
		pi_list->push_back(tmp);
		tmp.ms = 4500 + i * 4000; tmp.panel_no = 0; tmp.t = jubeat_online::game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 5500 + i * 4000; tmp.panel_no = 4; tmp.t = jubeat_online::game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 8; tmp.t = jubeat_online::game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 9; tmp.t = jubeat_online::game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
		tmp.ms = 7500 + i * 4000; tmp.panel_no = 12; tmp.t = jubeat_online::game::PlayRecord::RELEASE;
		pi_list->push_back(tmp);
	}
	
	playrecord->setJudgedList(std::move(pi_list));

	//�Ȃ��Đ�
	mus.startToPlay();	//���Oplay�ŗǂ���������

	jubeat_online::game::layers::SequencePlayer seqplayer(&seq, &mus, std::move(playrecord));


	a.addLayer(&bg, jubeat_online::graphics::layer::LayerManager::BACKGROUND, 0);
	a.addLayer(&frame, jubeat_online::graphics::layer::LayerManager::FOREGROUND, 0);
	a.addLayer(&musicinfo, jubeat_online::graphics::layer::LayerManager::MAIN, 0);
	a.addLayer(&shutterlayer, jubeat_online::graphics::layer::LayerManager::MAIN, 0);
	a.addLayer(&seqplayer, jubeat_online::graphics::layer::LayerManager::MAIN, 0);	//��ɒǉ��B�ԍ��͏d�����Ă��S�R���Ȃ��B
	
	

	a.process();

	return 0;
}