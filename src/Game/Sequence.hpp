#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"

namespace jubeon {
	namespace game {
		
		//Note��const�t�����\�b�h�݂̂�Read Only�Ȃ��߃X���b�h�Z�[�t
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
			/*
			bool operator == (Note n) { 
				return (n.duration == this->duration
					&& n.holdMarkerIndex == this->holdMarkerIndex
					&& n.justTime == this->justTime
					&& n.panelIndex == this->panelIndex);
			}*/
			
		};
		
		//Note��const�t�����\�b�h�݂̂�Read Only�Ȃ��߃X���b�h�Z�[�t
		class Sequence : protected std::vector<Note>{

		private:
			
			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence(void);

			//�R�s�[�R���X�g���N�^���֎~�B
			Sequence(const Sequence & cp);

		public:

			//������
			Sequence(const std::vector<Note> notes);
			
			const Note & operator[] (size_t idx) const;

			const Note & at(size_t idx) const;

			std::vector<Note>::const_iterator begin() const;

			std::vector<Note>::const_iterator end() const;

			std::vector<Note>::const_iterator search(const int ms) const;

			std::size_t size() const;
		};
	}
}

#endif