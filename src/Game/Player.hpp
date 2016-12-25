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

#include "Music.hpp"

namespace jubeon {
	namespace game {
		class Player {
		public:

			Player();

			virtual ~Player();


			////////////////////
			// Play
			////////////////////
		public:
			void initForPlay(strbuf::StreamBuffer<input::PanelInput> * panel_strbuf, const int playing_offset = 0);


			////////////////////
			// Marker
			////////////////////
		public:
			void setMarker(const std::shared_ptr<Marker> & new_marker);
			void setMarker(const Marker & new_marker);
			
			const Marker * getMarker(void) const;

		private:
			std::shared_ptr<Marker> marker;


			////////////////////
			// Input
			////////////////////
		public:
			PlayRecord * getPlayRecord(void);
			void updateInput(Sequence * seq);

		private:

			std::shared_ptr<strbuf::OutputStream<input::PanelInput>> panel_que;
			std::unique_ptr<PlayRecord> record;


			////////////////////
			// Music
			////////////////////
		public:			
			void setPlayerOffset(const int offset);
			int getPlayerOffset(void) const;
			int getCurrentTime(const Music * music) const;

		private:
			int offset;


		};
	}
}

#endif
