///////////////////////////////////
// (c) 2016 white
// Player class
///////////////////////////////////

#pragma once

#ifndef JUBEON_GAME_PLAYER_HPP
#define JUBEON_GAME_PLAYER_HPP

//shared_ptr
#include <memory>

//Marker class
#include "Marker.hpp"

//Event class
#include "Input/Event.hpp"

//PanelInput class
#include "Input/PanelInput.hpp"

//strbuf
#include "strbuf/strbuf.hpp"

//PlayRecord
#include "PlayRecord.hpp"

//Sequence
#include "Sequence.hpp"

//Music(only pointer)
#include "Music.hpp"

namespace jubeon {
	namespace game {
		class Player {
		public:

			Player(const std::string player_name);

			virtual ~Player();

			
			void initForPlay(strbuf::StreamBuffer<input::PanelInput> * panel_strbuf,
				std::vector<Note> & notes,
				const int playing_offset = 0);

			
			void setMarker(Marker * new_marker);
			const Marker * getMarker(void) const;
			
			PlayRecord * getPlayRecord(void) const;
			void updateInput(void);


			int getCurrentTime(const Music * music) const;

			const std::string name;

		private:
			Player();

			std::unique_ptr<Sequence> sequence;
			std::unique_ptr<PlayRecord> record;

			Marker * marker;
			
			std::shared_ptr<strbuf::OutputStream<input::PanelInput>> panel_que;
			
			int offset;
		};
	}
}

#endif
