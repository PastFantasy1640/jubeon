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



}

void jubeon::game::layers::SequencePlayer::Draw()
{
	//��ʃN���A
	this->clearBuffer();

	//�`��
	//Music�ɖ₢���킹�č��̍Đ��������擾
	const int mms = this->player->getCurrentTime(this->music);
	const int ms = mms - this->offset_ms;
	
	const int start_ms = ms - this->player->getMarker()->getLengthAfterMax();	//�t�Ȃ񂾂ȁ\
	const int end_ms = ms + this->player->getMarker()->getLengthBefore();

	{
		//### ���ʂ̕`�� ###
		//���ʕ\���̉\���̂���ms�́ACurrentMS - (disappear_time * 2)����ACurrentMS + appear_time
		//�S�čō�500ms�ł���Ɖ��肵��

		//�܂�ms�ȍ~��Sequence�̃C�e���[�^���擾


		Notes::const_iterator begin = this->sequence->search(start_ms);
		Notes::const_iterator end = this->sequence->search(end_ms);


		for (auto ite = begin; ite != end; ite++) {
			//�`�ʔ͈͓�

			if (ite->second != nullptr) {
				//������
				//�Ƃ������Ƃ͂��łɔ��肪�I����Ă���ꍇ�ł���B
				this->drawMarker(ms - ite->second->ms, ite, ite->second->judge);
			}
			else if (!ite->first.isHoldEnd()) {
				//�Ȃ�����
				//�܂��I����ĂȂ�
				//Marker�̃e�N�X�`�����擾
				//�z�[���h�G���h�}�[�J�[�͕`�ʂ��Ȃ�
				this->drawMarker(ms - ite->first.getJustTime(), ite, NOJUDGE);
			}

		}
	}
	
	/*
	�J������
	������Sequence�ŕ`�ʂł��Ȃ����Ɓ��z�[���h�G���h��Sequence��End�ɒB���Ă��Ȃ���
	�Ehold��second��nullptr����Ȃ�
	�Eend���ȍ~�ɏI���hold��`�ʂ���
	*/
	//�z�[���h�̕`��
	{
		for (auto ite = this->player->getPlayRecord()->getHoldingList()->begin(); ite != this->player->getPlayRecord()->getHoldingList()->end(); ite++) {
			if (ite->second != nullptr) {
				jMillisec hold_end_time = ite->first.getJustTime() + ite->first.getHoldDuration();
				if (hold_end_time >= end_ms) {
					//�`��
					this->drawMarker(ms - ite->second->ms, ite, ite->second->judge);
				}
			}
		}
	}
}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

void jubeon::game::layers::SequencePlayer::drawMarker(const jMillisec now_ms ,const Notes::const_iterator & ite, Judge judge)
{
	const sf::Texture * tex = this->player->getMarker()->getTexturePtr(now_ms, judge);
	if (tex != nullptr) {

		sf::Sprite markersp(*tex);

		const sf::IntRect & rect = this->panel_position->get(ite->first.getPanelIndex());

		markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
		markersp.setScale(static_cast<double>(rect.width) / tex->getSize().x, static_cast<double>(rect.height) / tex->getSize().y);
		this->draw(markersp);

	}
}

