#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"


namespace jubeat_online {
	namespace game {

		class Note{

		private:

			//�f�t�H���g�R���X�g���N�^�͋֎~
			Note();

		protected:
			
			//�W���X�g�^�C��(ms)
			int justTime;

			//�p�l���ԍ�(0-15)
			int panelIndex;

			//�z�[���h�̎���
			int duration;

			//�z�[���h�}�[�J�[�̏o���ʒu�p�l��
			int holdMarkerIndex;

			//���̃m�[�g�ɑ΂��锻��
			std::shared_ptr<PlayRecord::PanelInput> judged;
			
		public:
			
			//���ʂ̃}�[�J�[�̃R���X�g���N�^
			Note(const int just_time, const int panel_idx);

			//�z�[���h�}�[�J�[�̃R���X�g���N�^
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx);

			//�z�[���h�}�[�J�[�̃R���X�g���N�^
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx, const std::shared_ptr<PanelInput> judge);

			//�A�N�Z�T
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldMarkerIndex(void) const;

			//�W���b�W
			void getJudge(int * ms_diff, Judge * judge) const;
			
		};

		typedef std::vector<Note> Notes;
		typedef std::shared_ptr<Notes> SPNotes;

		class Sequence {

		private:
			//���ʖ{��
			SPNotes notes;
			
			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence();

			//�R�s�[�R���X�g���N�^���֎~�B
			Sequence(const Sequence & cp);

		public:

			//������
			//���[�h�܂ł͂��Ȃ�
			Sequence(const std::vector<Note> notes);
			
			//�m�[�g���擾
			SPNotes getNotes(void);
			
		};
	}
}

#endif