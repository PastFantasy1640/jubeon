#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>


namespace jubeat_online {
	namespace game {
		
		typedef struct Note {
			int justTime;
			int panelIndex;
			int duration;
			Note()
				: justTime(0),
				panelIndex(0),
				duration(0) {};
		} Note;

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