#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include "Note.hpp"


namespace jubeat_online {
	namespace game {
		class Sequence {

			//���ʖ{��
			std::vector<Note> notes;
			std::vector<HoldNote> hold_notes;

			//���ʖ�
			std::string filename;

			//�f�t�H���g�R���X�g���N�^�͋֎~
			Sequence();

			//�R�s�[�R���X�g���N�^���֎~�B
			Sequence(const Sequence & cp);

			//���[�h������
			bool is_loaded;

		public:

			//������
			//���[�h�܂ł͂��Ȃ�
			Sequence(const std::string & filename);

			//���ʂ̃��[�h
			bool load(void);

			//���ʂ̔j��
			void deleteNotes(void);

			//get�A�N�Z�T
			const std::vector<Note> * getNotes() const;
			const std::vector<HoldNote> * getHoldNote() const;
			std::string getNotesFileName(void) const;

			//���[�h������
			bool isLoad(void) const;
			
		};
	}
}

#endif