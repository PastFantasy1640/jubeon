//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/ListenPanel.hpp"

//for logging
#include "Systems/Logger.hpp"


//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	std::shared_ptr<jubeon::game::Sequence> sequence,
	std::shared_ptr<jubeon::game::Music> music,
	std::shared_ptr<jubeon::game::PlayRecord> playrecord,
	std::shared_ptr<std::map<const size_t, size_t>> seq_pr_mapping,
	std::shared_ptr<jubeon::game::PanelPosition> panel_position,
	int offset_ms)
	: sequence(sequence), music(music), playrecord(playrecord), seq_pr_mapping(seq_pr_mapping), panel_position(panel_position), offset_ms(offset_ms)
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
	const int mms = this->music->getPlayingCurrentTime();
	const int ms = this->music->getPlayingCurrentTime() - this->offset_ms;



	//### ���ʂ̕`�� ###
	//���ʕ\���̉\���̂���ms�́ACurrentMS - (disappear_time * 2)����ACurrentMS + appear_time
	//�S�čō�500ms�ł���Ɖ��肵��
	const int start_ms = ms - 1000;
	const int end_ms = ms + 500;

	//�܂�ms�ȍ~��Sequence�̃C�e���[�^���擾
	std::vector<Note>::const_iterator ite_n = this->sequence->search(start_ms);
	size_t sequence_idx = std::distance(this->sequence->begin(), ite_n);

	//����ȍ~�Ń}�b�s���O���m�F���Ă���
	for (; sequence_idx < this->sequence->size(); sequence_idx++){
		if (this->sequence->at(sequence_idx).getJustTime() > end_ms) break;	//�`�ʔ͈͊O

		//�}�b�s���O�����邩
		
		const std::map<const size_t, size_t>::const_iterator jpi = this->seq_pr_mapping->find(sequence_idx);
		if (jpi != this->seq_pr_mapping->end()) {
			//������
			//�Ƃ������Ƃ͂��łɔ��肪�I����Ă���ꍇ�ł���B
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(mms - this->playrecord->getJudgedList()->at(jpi->second).ms, this->playrecord->getJudgedList()->at(jpi->second).judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(this->playrecord->getJudgedList()->at(jpi->second).panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//�Ȃ�����
			//�܂��I����ĂȂ�
			//Marker�̃e�N�X�`�����擾
			const sf::Texture * tex = this->mk->getTexturePtr(ms - this->sequence->at(sequence_idx).getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(this->sequence->at(sequence_idx).getPanelIndex());

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

