////////////////////////////////////////////////////////////
// (c) 2016 white PanelInput.hpp
////////////////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_GAME_PANELINPUT_HPP
#define JUBEON_GAME_PANELINPUT_HPP

//for jubeon::Type
#include "Game/TypeDefinition.hpp"

//for type definition of note member
#include "Game/NoteDefinition.hpp"

#include "Event.hpp"

//namespace is jubeon::input
namespace jubeon {
	namespace input {

		//structure
		class PanelInput {
		public:
			const jPanel	panel_no;		//PanelNo
			const jubeon::Type	t;				//Type(PUSH or RELEASE)
			const jMillisec		ms;				//millisecond

			
			//Args Constructor
			PanelInput(unsigned char panel_no, jubeon::Type t, unsigned int ms)
				: panel_no(panel_no), t(t), ms(ms) {}


			//Default Constructor
			PanelInput() : panel_no(0), t(RELEASE), ms(0) {}

		
		private:

		};
	
	};
};

#endif