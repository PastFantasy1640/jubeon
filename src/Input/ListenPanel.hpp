///////////////////////////////////////////////////
// (c) 2016 white
//
//   *** REBUILDING LISTENPANEL CLASS ***
//
///////////////////////////////////////////////////

#pragma once

#ifndef JUBEAT_ONLINE_PANEL_LISTEN_H_
#define JUBEAT_ONLINE_PANEL_LISTEN_H_


#include <mutex>
#include <atomic>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

#include "PanelInput.hpp"


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

            /** Create the thread listening to panel input and process.
             */
			void startThread(void);

			/** Closing the thread. This function is available while the thread is running.
			 */
			void Close(void);

			/** Get the list logged panel pushed or released (type is std::vector).
			 * @returns The panel log list.
			 */
			std::vector<PanelInput> getEvent(void);

            /** Get the quing num.
             * @return Current que size.
             */
			std::size_t getQueNum(void) const;

            /** Set flag whether panel status que or not.
             * @param flag true, and que is available.
             */
			void setListenFlag(const bool flag);

            /** Get flag whether panel status que or not.
             * @returns true, and que is available.
             */
			bool getListenFlag(void) const;

            /** Get flag whether the que has overflowed or not.
             * max que size depends MAXQUE_SIZE.
             * When this function is called, the flag is clear.
             * @return true, and the que has overflowed.
             */
			bool isOverflow(void) const;

            /** Restart the timer. 
            
             */
			void restartTimer(const int offset);


			std::atomic<int> offset;

        private:
			sf::Clock panel_clock_;
			std::list<PanelInput> que_;

			bool is_queue_;
			bool is_overflow_;

			std::atomic<bool> is_thread_exit_;


			std::mutex mtx_;
			void GetPanelThread(void);

			bool pushing_[16];

			void SetQue(const int n);


		};
	}

}


#endif
