#pragma once

#ifndef JUBEAT_ONLINE_NOTE_HPP
#define JUBEAT_ONLINE_NOTE_HPP

namespace jubeat_online {
	namespace game {
		class Note {
		public:
			//TO DO : ç°ÇæÇØ
			
			unsigned char panel_no;
			unsigned int ms;

			Note(const unsigned char panel_no, const unsigned int ms);
			
		};

		class HoldNote : public Note {
		public:
			unsigned char appear_panel_no;
			unsigned int holdend_ms;

			HoldNote(const unsigned char panel_no, const unsigned int ms, unsigned char appear_panel_no, unsigned int holdend_ms);
		};
	}
}

#endif