#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"

namespace jubeon {
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

			//�z�[���h�̎���(0�̏ꍇ�̓^�b�`���ʁj
			int duration;

			//�z�[���h�}�[�J�[�̏o���ʒu�p�l��
			int holdMarkerIndex;

			
		public:
			
			//���ʂ̃}�[�J�[�̃R���X�g���N�^
			Note(const int just_time, const int panel_idx);

			//�z�[���h�}�[�J�[�̃R���X�g���N�^
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx);


			//�A�N�Z�T
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldMarkerIndex(void) const;
			bool isHold(void) const;

			
		};

		typedef std::vector<Note> Notes;
		typedef std::shared_ptr<Notes> SPNotes;

		class Sequence : protected SPNotes{

		private:
			
			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence();

			//�R�s�[�R���X�g���N�^���֎~�B
			Sequence(const Sequence & cp);

		public:

			//������
			Sequence(const SPNotes notes);
						
		};
	}
}

#endif