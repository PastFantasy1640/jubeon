//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/ListenPanel.hpp"

//for logging
#include "Systems/Logger.hpp"

//for getting resource
#include "Storages/ResourceManager.hpp"
#include "Storages/FontManager.hpp"

//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	std::shared_ptr<jubeon::game::Sequence> sequence,
	std::shared_ptr<jubeon::game::Music> music,
	std::shared_ptr<jubeon::game::PlayRecord> playrecord,
	std::shared_ptr<std::map<const Note *, const JudgedPanelInput *>> seq_pr_mapping,
	std::shared_ptr<jubeon::game::PanelPosition> panel_position,
	int offset_ms)
	: sequence(sequence), music(music), playrecord(playrecord), seq_pr_mapping(seq_pr_mapping), panel_position(panel_position), offset_ms(offset_ms)
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

//Initialize
void jubeon::game::layers::SequencePlayer::Init()
{
	//����������

	//�p�l���g�̓ǂݍ���
	storage::ResourceManager::getTexture("media/image/panel_shadow.png");



	//###################TEMPORARY####################
	//�}�[�J�[�}�l�[�W���|�݂����Ȃ̂�p�ӂ���
	//�}�[�J�[�ǂݍ��݃e�X�g
	this->mk.reset(new Marker("media/marker/shutter","shutter.json"));
	if (!this->mk->load()) {
		systems::Logger::error("�}�[�J�[���ǂݍ��߂܂���ł���");
	}


	//��ʃv�b�V���͖���
	this->pushing = 0;
}

void jubeon::game::layers::SequencePlayer::Draw()
{
	//��ʃN���A
	this->clearBuffer();

	//�`��
	//Music�ɖ₢���킹�č��̍Đ��������擾
	const int mms = this->music->getPlayingCurrentTime();
	const int ms = this->music->getPlayingCurrentTime() - this->offset_ms;



	//### ���ʂ̕`�� ###
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
			const sf::Texture * tex = this->mk->getTexturePtr(ms - jpi->second->ms, jpi->second->judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(jpi->second->panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//�Ȃ�����
			//�܂��I����ĂȂ�
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite_n->getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(ite_n->getPanelIndex());

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		
		}
	}





	//### �p�l���t���[���̕\�� ###
	//�ǂ̃p�l����������Ă������A�O�񒲍�����ms���L�^���Ă��� ->before_check_ms

	//�������Abcm�ȑO��PanelInput��ǉ�����ꍇ�́Abcm�����̎��Ԃ܂ň����߂��ċL�^����B
	//�܂��Abcm�̎��Ԃ̏ꏊ���ɓ񕪒T���ɂĒT���o��
	auto p = this->playrecord->getIteratorFromTime(*this->playrecord->getJudgedList(), this->before_check_ms);
	
	//�O�񒲍��ƍ��񒲍���ms�������ꍇ�̓X�L�b�v���Ă����B
	//�Ⴄ�ꍇ�̂ݍX�V
	if (this->before_check_ms != mms) {

		//����ȍ~����A���݂�ms�܂ł���`��͂��A�p�l���̉�����Ԃ��X�V����
		for (; p != this->playrecord->getJudgedList()->end(); p++) {
			//���̏������ƂɁA�����ɂ��g���̃O���f�[�V�����`�ʁA�������́A�z�[���h���ʂ̕`�ʂɎg���B
			if ((*p).ms > mms) break;	//�����V�����Ƃ���֍s�����ꍇ�A��͂͏I��

			if ((*p).t) {
				//����
				this->setPushing((*p).panel_no);
			}
			else {
				//������
				this->setReleasing((*p).panel_no);
			}

			//�������A�Ȃ������߂����肵�āA�`�ʂ���V���Ȃ���΂Ȃ�Ȃ��ꍇ�Abcm��0ms���w�肵�A�S�X�V���Ȃ��Ă͂Ȃ�Ȃ��B

		}

		this->before_check_ms = mms - 1000;

	}

	sf::Text text("ms:" + std::to_string(ms), storage::FontManager::getFont("media/fonts/Frutiger.TTF"));
	text.setColor(sf::Color::Black);
	this->draw(text);
	text.setString("mms:" + std::to_string(mms));
	text.setPosition(0, 100);
	this->draw(text);
	text.setString("panelms:" + std::to_string(input::ListenPanel::panel_clock_->getElapsedTime().asMilliseconds() - input::ListenPanel::offset));
	text.setPosition(0, 130);
	this->draw(text);
	text.setString("diff ms:" + std::to_string(input::ListenPanel::panel_clock_->getElapsedTime().asMilliseconds() - input::ListenPanel::offset - mms));
	text.setPosition(0, 160);
	this->draw(text);

	//�ŏI�I��push����Ă�ꏊ�ɕ`��
	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			const sf::Texture & pframe = storage::ResourceManager::getTexture("media/image/panel_shadow.png");
			sf::Sprite sp(pframe);
			const sf::IntRect & rect = this->panel_position->get(i);

			sp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			sp.setScale(PanelPosition::get_ex(pframe.getSize().x, rect.width), PanelPosition::get_ex(pframe.getSize().y, rect.height));
			this->draw(sp);
		}
	}
}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

