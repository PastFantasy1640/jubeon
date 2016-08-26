///////////////////////////////////////////////////
// (c) 2016 white
//
//   *** REBUILDING LISTENPANEL CLASS ***
//
///////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_INPUT_LISTENPANEL_HPP
#define JUBEON_INPUT_LISTENPANEL_HPP

//Clock
#include <SFML/Graphics.hpp>

//PanelInput
#include "PanelInput.hpp"

//Que Stream
#include "strbuf/strbuf.hpp"

//memory
#include <memory>

//thread safe
#include <atomic>

//array
#include <array>

//thread
#include <thread>

#include "Graphics/Layer/LayerManager.hpp"

namespace jubeon {
	namespace input {
		class ListenPanel {
		public:
            /** @dupricate  */
			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2,
			};

            static const std::size_t QUEUE_MAXSIZE = 1024;

            /** Listening to panel input and process.
             */
			void process(jubeon::graphics::LayerManager * main_window);

            /** Restart the timer. 
             */
			void restartTimer(const int offset);
			
			
			/** get Instance
			 */
			static ListenPanel * getInstance();

			// Destructor
			~ListenPanel();
        private:
			
			// Constructor
			ListenPanel();
			
			// Clocking
			sf::Clock panel_clock_;
			
			// Input Stream
			std::shared_ptr<strbuf::InputStream<sf::Event>> input;

            // Thread Function
			void ThreadFunc(jubeon::graphics::LayerManager * main_window);
			
			// Set Queue
			//void SetQue(const int n);

            //pushing flag
			std::array<bool, 16> push_flags;
			
			//offset
			std::atomic<int> offset;

			//sigleton instance
			static std::unique_ptr<ListenPanel> instance;

		};
	}

}


#endif
