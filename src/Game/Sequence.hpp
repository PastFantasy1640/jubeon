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
			//0xff�̏ꍇ�̓z�[���h�}�[�J�[�I���n�_
			//isHold��true�AisHoldEnd��true�ɂȂ�B
			const jPanel holdMarkerIndex;

		public:
			
			static const jPanel HOLD_END = 0xFF;

			//���ʂ̃}�[�J�[�̃R���X�g���N�^
			Note(const jMillisec just_time, const jPanel panel_idx, const bool is_hold_end = false);

			//�z�[���h�}�[�J�[�̃R���X�g���N�^
			Note(const jMillisec just_time, const jPanel panel_idx, const int duration, const int holdmarker_panel_idx);


			//�A�N�Z�T
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldEndTime(void) const;
			int getHoldMarkerIndex(void) const;
			bool isHold(void) const;
			bool isHoldEnd(void) const;

		};
	
		typedef std::pair<const Note, JudgedPanelInput *> NoteJudgePair;
		class Notes : protected std::vector<NoteJudgePair> {
		protected:
		public:
			using std::vector<NoteJudgePair>::const_iterator;
			using std::vector<NoteJudgePair>::operator[];
			using std::vector<NoteJudgePair>::at;
			using std::vector<NoteJudgePair>::begin;
			using std::vector<NoteJudgePair>::end;
			using std::vector<NoteJudgePair>::size;
			using std::vector<NoteJudgePair>::empty;
			Notes::const_iterator jubeon::game::Notes::search(const jMillisec ms) const;
		};

		//Note��const�t�����\�b�h�݂̂�Read Only�Ȃ��߃X���b�h�Z�[�t
		class Sequence : public Notes{

		private:
			
			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence(void);


		public:

			Sequence(const Sequence & cp);

			//������
			Sequence(const std::vector<Note> notes);
			
			void setJudgedPanelInput(const Notes::const_iterator target, JudgedPanelInput * judged);

		};
	}
}

#endif