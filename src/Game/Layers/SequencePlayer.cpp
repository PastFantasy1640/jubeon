#include "SequencePlayer.hpp"

#include <memory>

#include <iostream>

#include "../PlayRecord.hpp"
#include "../../Input/PanelEvent.hpp"

jubeat_online::game::layers::SequencePlayer::SequencePlayer(const Sequence * sequence, Music * music, std::unique_ptr<PlayRecord> playrecord)
	: LayerBase(),
	sequence(sequence),
	music(music),
	playrecord(std::move(playrecord)),
	before_check_ms(0),
	pushing(0),
	mk("media/marker/shutter", "shutter.json")
{
}

void jubeat_online::game::layers::SequencePlayer::process(void)
{
	//process�֐��ł́A���ʂ̔�����s���܂��B
	
	//PlayRecord���疢���蕪���擾����
	PlayRecord::NoJudgedList no_judge_list = this->playrecord->getNoJudgedList();

	//Sequence����C���X�^���X���擾����
	//�擾�ς݂ł��i�����o�j

	//���菈��
	//TO DO : ����
	//���̂Ƃ���S��NOJUDGE
	unsigned int music_ms = this->music->getPlayingCurrentTime();
	unsigned int panel_ms = this->playrecord->getTime();
	int diff_ms = panel_ms - music_ms;

	for (auto p : *no_judge_list) {
		p.j = Judge::NOJUDGE;	//TEMPORARY
		p.ms -= diff_ms;	//�Ȃ�ms��
		if (p.ms <= this->before_check_ms) this->before_check_ms = p.ms;	//�����߂�
	}

	//PlayRecord�֔�����X�V
	this->playrecord->setJudgedList(std::move(no_judge_list));

	//ShutterLayer��K�X�X�V
	//TO DO : �܂�����ĂȂ�

	//MusicBar��K�X�X�V
	//TO DO : �܂�(ry
}

void jubeat_online::game::layers::SequencePlayer::Init()
{
	//����������

	//�p�l���g�̓ǂݍ���
	this->panel_frame.loadFromFile("media/image/panel_shadow.png");
	//panel_shadow.png�̓T�C�Y190x190
	//�L�k������\��������̂ŁAsmooth�K�p
	this->panel_frame.setSmooth(true);

	//�}�[�J�[�ǂݍ��݃e�X�g
	this->mk.load();


}

void jubeat_online::game::layers::SequencePlayer::Draw()
{

	this->clearBuffer();

	//�`��

	//Music�ɖ₢���킹�č��̍Đ��������擾
	const unsigned int ms = this->music->getPlayingCurrentTime();

	//Sequence����C���X�^���X���擾
	//��

	//PlayRecord����C���X�^���X���擾
	//�ρA�Ƃ����������Ă�

	//Marker�̃e�N�X�`�����擾
	const sf::Texture * tex = this->mk.getTexturePtr((this->music->getPlayingCurrentTime() % 2000) - 1000, PERFECT);
	if (tex != nullptr) {

		sf::Sprite markersp(*tex);
		markersp.setPosition(100, 100);
		markersp.setScale(163.0f / tex->getSize().x, 163.0f / tex->getSize().y);
		this->draw(markersp);

	}
	//�`��


	//*****************�Ƃ肠�������̓e�X�g�Ƃ��āA

	//Marker�̃e�N�X�`���擾�͂��Ƃ���
	//perfect�^�C����0ms�Ƃ��āA������������ꍇ�͕���ms�A�x���ꍇ�͐���ms
	//�w�肵�Ċ֐����Ăׂ΁A�Ή�����}�[�J�[�t���[���̃e�N�X�`�����Ԃ����
	//����ŕ`�ʁAok
	
	auto to_binString = [](unsigned int val)
	{
		if (!val)
			return std::string("0");
		std::string str;
		while (val != 0) {
			if ((val & 1) == 0)  // val �͋������H
				str.insert(str.begin(), '0');  //  �����̏ꍇ
			else
				str.insert(str.begin(), '1');  //  ��̏ꍇ
			val >>= 1;
		}
		return str;
	};


	//������Ă�Ƃ��̃}�[�J�[��������낤
	//�ǂ̃p�l����������Ă������A�O�񒲍�����ms���L�^���Ă��� ->before_check_ms

	//�������Abcm�ȑO��PanelInput��ǉ�����ꍇ�́Abcm�����̎��Ԃ܂ň����߂��ċL�^����B
	//�܂��Abcm�̎��Ԃ̏ꏊ���ɓ񕪒T���ɂĒT���o��
	auto p = this->playrecord->getPanelInputFromTime(this->before_check_ms);
	
	//�O�񒲍��ƍ��񒲍���ms�������ꍇ�̓X�L�b�v���Ă����B
	//�Ⴄ�ꍇ�̂ݍX�V
	if (this->before_check_ms != ms) {

		//����ȍ~����A���݂�ms�܂ł���`��͂��A�p�l���̉�����Ԃ��X�V����
		for (; p != this->playrecord->getPanelInputListEnd(); p++) {
			//���̏������ƂɁA�����ɂ��g���̃O���f�[�V�����`�ʁA�������́A�z�[���h���ʂ̕`�ʂɎg���B
			if ((*p).ms > ms) break;	//�����V�����Ƃ���֍s�����ꍇ�A��͂͏I��

			if ((*p).t) {
				//����
				this->setPushing((*p).panel_no);
				std::cout << "����" << ms << "ms:�O��" << this->before_check_ms << "ms:" << to_binString(this->pushing) << "\n";
			}
			else {
				//������
				this->setReleasing((*p).panel_no);
				std::cout << "����" << ms << "ms:" << to_binString(this->pushing) << "\n";
			}

			//�������A�Ȃ������߂����肵�āA�`�ʂ���V���Ȃ���΂Ȃ�Ȃ��ꍇ�Abcm��0ms���w�肵�A�S�X�V���Ȃ��Ă͂Ȃ�Ȃ��B

		}

		this->before_check_ms = ms;

	}

	//�ŏI�I��push����Ă�ꏊ�ɕ`��
	//TO DO : �p�l�����ƏƂ炵���킹�Ȃ���

	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			//sf::RectangleShape test(sf::Vector2f(163.0f, 163.0f));
			//test.setFillColor(sf::Color::Red);
			//test.setPosition(200 + (i % 4) * 170, 200 + (i / 4) * 170);
			//�g�̑傫����163
			//�g�̑�����38
			//0�Ԗڂ̃p�l���̍�����W��(1,593)
			sf::Sprite sp(this->panel_frame);
			sp.setPosition(1 + (i % 4) * (163 + 38), 593 + (i / 4) * (163 + 38));
			sp.setScale(163.0f / 190.0f, 163.0f / 190.0f);
			this->draw(sp);
		}
	}



}

void jubeat_online::game::layers::SequencePlayer::Exit()
{
}
