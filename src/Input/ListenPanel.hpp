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
			void startListenThread(void);

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
			std::size_t getQueNum(void);

            /** Set flag whether panel status que or not.
             * @param flag true, and que is available.
             */
			void setListenFlag(const bool flag);

            /** Get flag whether panel status que or not.
             * @returns true, and que is available.
             */
			bool getListenFlag(void);

            /** Get flag whether the que has overflowed or not.
             * max que size depends MAXQUE_SIZE.
             * @return true, and the que has overflowed.
             */
			bool isOverflow(void);

			static void setTime(const int offset);

			static sf::Clock panel_clock_;

			static std::atomic<int> offset;
		private:
			static std::list<PanelInput> que_;

			static bool is_queue_;
			static bool is_overflow_;

			static std::atomic<bool> is_thread_exit_;


			static std::mutex mtx_;
			static void GetPanelThread(void);

			static bool pushing_[16];

			static void SetQue(const int n);


		};
	}

}


#endif
