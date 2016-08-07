#include "SequencePlayer.hpp"

#include <memory>

#include <iostream>

#include "../PlayRecord.hpp"

#include "Systems/Logger.hpp"


jubeon::game::layers::SequencePlayer::SequencePlayer(
	std::shared_ptr<jubeon::game::Sequence> sequence,
	std::shared_ptr<jubeon::game::Music> music,
	std::shared_ptr<jubeon::game::PlayRecord> playrecord,
	std::shared_ptr<std::map<const Note *, const JudgedPanelInput *>> seq_pr_mapping,
	std::shared_ptr<jubeon::game::PanelPosition> panel_position)
	: sequence(sequence), music(music), playrecord(playrecord), seq_pr_mapping(seq_pr_mapping), panel_position(panel_position)
{
}
/*
void jubeon::game::layers::SequencePlayer::process(void)
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
*/
void jubeon::game::layers::SequencePlayer::Init()
{
	//����������

	//�p�l���g�̓ǂݍ���
	this->panel_frame.loadFromFile("media/image/panel_shadow.png");
	//panel_shadow.png�̓T�C�Y190x190
	//�L�k������\��������̂ŁAsmooth�K�p
	this->panel_frame.setSmooth(true);

	//�}�[�J�[�ǂݍ��݃e�X�g
	this->mk.reset(new Marker("media/marker/shutter","shutter.json"));
	if (!this->mk->load()) {
		systems::Logger::error("�}�[�J�[���ǂݍ��߂܂���ł���");
	}

	this->pushing = 0;
}

void jubeon::game::layers::SequencePlayer::Draw()
{

	this->clearBuffer();

	//�`��

	//Music�ɖ₢���킹�č��̍Đ��������擾
	const unsigned int ms = this->music->getPlayingCurrentTime();

	//Sequence����C���X�^���X���擾
	//��

	//PlayRecord����C���X�^���X���擾
	//�ρA�Ƃ����������Ă�

	//���ʕ\���̉\���̂���ms�́ACurrentMS - (disappear_time * 2)����ACurrentMS + appear_time
	//�S�čō�500ms�ł���Ɖ��肵��
	const int start_ms = ms - 1000;
	const int end_ms = ms + 500;

	//�܂�ms�ȍ~��Sequence�̃C�e���[�^���擾
	std::vector<Note>::const_iterator ite_n = this->sequence->search(start_ms);

	//����ȍ~�Ń}�b�s���O���m�F���Ă���
	for (; ite_n != this->sequence->end(); ite_n++) {
		if (ite_n->getJustTime() > end_ms) break;	//�`�ʔ͈͊O

		//�}�b�s���O�����邩
		
		const std::map<const Note *, const JudgedPanelInput *>::const_iterator jpi = this->seq_pr_mapping->find(&(*ite_n));
		if (jpi != this->seq_pr_mapping->end()) {
			//������
			//�Ƃ������Ƃ͂��łɔ��肪�I����Ă���ꍇ�ł���B
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(this->music->getPlayingCurrentTime() - jpi->second->ms, jpi->second->judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(jpi->second->panel_no);

				markersp.setPosition(rect.left,rect.top);
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//�Ȃ�����
			//�܂��I����ĂȂ�
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(this->music->getPlayingCurrentTime() - ite_n->getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(ite_n->getPanelIndex());

				markersp.setPosition(rect.left, rect.top);
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		
		}
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
	auto p = this->playrecord->getIteratorFromTime(*this->playrecord->getJudgedList(), this->before_check_ms);
	
	//�O�񒲍��ƍ��񒲍���ms�������ꍇ�̓X�L�b�v���Ă����B
	//�Ⴄ�ꍇ�̂ݍX�V
	if (this->before_check_ms != ms) {

		//����ȍ~����A���݂�ms�܂ł���`��͂��A�p�l���̉�����Ԃ��X�V����
		for (; p != this->playrecord->getJudgedList()->end(); p++) {
			//���̏������ƂɁA�����ɂ��g���̃O���f�[�V�����`�ʁA�������́A�z�[���h���ʂ̕`�ʂɎg���B
			if ((*p).ms > ms) break;	//�����V�����Ƃ���֍s�����ꍇ�A��͂͏I��

			if ((*p).t) {
				//����
				this->setPushing((*p).panel_no);
				//std::cout << "����" << ms << "ms:�O��" << this->before_check_ms << "ms:" << to_binString(this->pushing) << "\n";
			}
			else {
				//������
				this->setReleasing((*p).panel_no);
				//std::cout << "����" << ms << "ms:" << to_binString(this->pushing) << "\n";
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
			const sf::IntRect & rect = this->panel_position->get(i);

			sp.setPosition(rect.left, rect.top);
			sp.setScale(PanelPosition::get_ex(this->panel_frame.getSize().x, rect.width), PanelPosition::get_ex(this->panel_frame.getSize().y, rect.height));
			this->draw(sp);
		}
	}



}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

