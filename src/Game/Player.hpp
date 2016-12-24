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

namespace jubeon {
	namespace game {
		class Player {
		public:

			Player();

			virtual ~Player();


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

			void setInputFromEvent(input::Event & instance);
			void setInputFromNetwork();	//TO DO
			const PlayRecord * getPlayRecord(void) const;
			void updateInput(Sequence & seq);

		private:
			std::shared_ptr<strbuf::OutputStream<input::EventContainer>> event_output;
			std::shared_ptr<strbuf::InputStream<input::PanelInput>> pinput_input;
			std::shared_ptr<strbuf::OutputStream<input::PanelInput>> pinput_output;
			strbuf::StreamBuffer<input::PanelInput> pinput_sb;
			PlayRecord record;

		};
	}
}

#endif
