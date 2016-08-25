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
			void process(void);

			/** Closing the thread. This function is available while the thread is running.
			 */
			void Close(void);


            /** Set flag whether panel status que or not.
             * @param flag true, and que is available.
             */
			void setListenFlag(const bool flag);

            /** Get flag whether panel status que or not.
             * @returns true, and que is available.
             */
			bool isListening(void) const;


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
			
			//thread
			std::unique_ptr<std::thread> check_th_;
			
			// Clocking
			sf::Clock panel_clock_;
			
			// Que Stream Buffer
			strbuf::StreamBuffer<PanelInput> quebuf;
			
			// Input Stream
			std::shared_ptr<strbuf::InputStream<PanelInput>> input;

            // is Queue flag
			std::atomic<bool> is_queue_;

            // thread will close
			std::atomic<bool> is_thread_exit_;

            // time offset
			std::atomic<int> offset;

            // Thread Function
			void ThreadFunc(void);
			
			// Set Queue
			void SetQue(const int n);

            //pushing flag
			std::array<bool, 16> push_flags;

			//sigleton instance
			static std::unique_ptr<ListenPanel> instance;

		};
	}

}


#endif
