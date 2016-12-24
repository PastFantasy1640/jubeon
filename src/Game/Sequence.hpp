#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"
#include "NoteDefinition.hpp"
#include "JudgedPanelInput.hpp"

namespace jubeon {
	namespace game {
		
		//Note��const�t�����\�b�h�݂̂�Read Only�Ȃ��߃X���b�h�Z�[�t
		class Note{


		private:

			//�f�t�H���g�R���X�g���N�^�͋֎~
			Note();

			void operator=(Note & n);


		protected:
			
			//�W���X�g�^�C��(ms)
			const jMillisec justTime;

			//�p�l���ԍ�(0-15)
			const jPanel panelIndex;

			//�z�[���h�̎���(0�̏ꍇ�̓^�b�`���ʁj
			const jMillisec duration;

			//�z�[���h�}�[�J�[�̏o���ʒu�p�l��
			const jPanel holdMarkerIndex;

			
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
	
		typedef std::pair<const Note, JudgedPanelInput *> NoteJudgePair;
		typedef std::vector<NoteJudgePair> Notes;

		//Note��const�t�����\�b�h�݂̂�Read Only�Ȃ��߃X���b�h�Z�[�t
		class Sequence : protected Notes{

		private:
			
			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence(void);


		public:

			Sequence(const Sequence & cp);

			//������
			Sequence(const std::vector<Note> notes);

			Notes::const_iterator jubeon::game::Sequence::search(const jMillisec ms) const;
			
			using Notes::const_iterator;
			using Notes::operator[];
			using Notes::at;
			using Notes::begin;
			using Notes::end;
			using Notes::size;
			using Notes::empty;

			void setJudgedPanelInput(const Notes::const_iterator target, JudgedPanelInput * judged);

		};
	}
}

#endif