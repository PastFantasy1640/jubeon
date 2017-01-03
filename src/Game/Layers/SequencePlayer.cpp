//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/Event.hpp"

//for logging
#include "Systems/Logger.hpp"


//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	const Sequence * sequence,
	const Music * music,
	const Player * player,
	const jubeon::game::PanelPosition * panel_position,
	int offset_ms)
	: sequence(sequence), music(music), player(player), panel_position(panel_position), offset_ms(offset_ms)
{
}




//Initialize
void jubeon::game::layers::SequencePlayer::Init()
{
	//����������



	//###################TEMPORARY####################
	//�}�[�J�[�}�l�[�W���|�݂����Ȃ̂�p�ӂ���
	//�}�[�J�[�ǂݍ��݃e�X�g
	this->mk.reset(new Marker("media/marker/shutter","shutter.json"));
	if (!this->mk->load()) {
		systems::Logger::error("�}�[�J�[���ǂݍ��߂܂���ł���");
	}


}

void jubeon::game::layers::SequencePlayer::Draw()
{
	//��ʃN���A
	this->clearBuffer();

	//�`��
	//Music�ɖ₢���킹�č��̍Đ��������擾
	const int mms = this->player->getCurrentTime(this->music);
	const int ms = mms - this->offset_ms;



	//### ���ʂ̕`�� ###
	//���ʕ\���̉\���̂���ms�́ACurrentMS - (disappear_time * 2)����ACurrentMS + appear_time
	//�S�čō�500ms�ł���Ɖ��肵��
	const int start_ms = ms - this->mk->getLengthAfterMax();	//�t�Ȃ񂾂ȁ\
	const int end_ms = ms + this->mk->getLengthBefore();

	//�܂�ms�ȍ~��Sequence�̃C�e���[�^���擾
	
	jMillisec hold_max_time = 0;
	
	for (auto hold = this->player->getPlayRecord()->getHoldingList()->begin(); hold != this->player->getPlayRecord()->getHoldingList()->end(); hold++) {
		if (hold->second != nullptr) {
			jMillisec hold_end_time = hold->first.getJustTime() + hold->first.getHoldDuration();
			if (hold_max_time < hold_end_time) hold_max_time = hold_end_time;
		}
	}

	Notes::const_iterator begin = this->sequence->search(start_ms);
	Notes::const_iterator end = this->sequence->search((end_ms > hold_max_time ? end_ms : hold_max_time));


	for (auto ite = begin; ite != end; ite++) {
		//�`�ʔ͈͓�

		if (ite->second != nullptr) {
			//������
			//�Ƃ������Ƃ͂��łɔ��肪�I����Ă���ꍇ�ł���B
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite->second->ms, ite->second->judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(ite->second->panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else if(!ite->first.isHoldEnd()){
			//�Ȃ�����
			//�܂��I����ĂȂ�
			//Marker�̃e�N�X�`�����擾
			//�z�[���h�G���h�}�[�J�[�͕`�ʂ��Ȃ�
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite->first.getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(ite->first.getPanelIndex());

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}

		}
	
	}




}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

