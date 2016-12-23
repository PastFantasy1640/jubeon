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
			strbuf::StreamBuffer<input::Event> event_sb;
			strbuf::StreamBuffer<input::PanelInput> pinput_sb;



		private:


		};
	}
}

#endif
