///////////////////////////////////////////////////
// (c) 2016 white
//
//   *** REBUILDING LISTENPANEL CLASS ***
//
///////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_INPUT_EVENT_HPP
#define JUBEON_INPUT_EVENT_HPP

//Clock, Event
#include <SFML/Graphics.hpp>

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

//to get event
#include "Graphics/Layer/LayerManager.hpp"

//mapping
#include <unordered_map>

namespace jubeon {
	namespace input {
		typedef struct EventContainer{
			sf::Event e;
			sf::Time time;
			EventContainer() {}
			EventContainer(const sf::Event & e, const sf::Time time) : e(e), time(time) {}
		}EventContainer;

		class Event : protected strbuf::StreamBuffer<EventContainer>{
		public:

            static const std::size_t QUEUE_MAXSIZE = 1024;

            /** Listening to panel input and process.
             */
			void process(jubeon::graphics::LayerManager * main_window);

            /** Restart the timer. 
             */
			void restartTimer(const int offset);
			
			/** set OutputStream
			 */
			using strbuf::StreamBuffer<EventContainer>::addOutputStream;

			/** get Instance
			 */
			static Event * getInstance(const jubeon::graphics::LayerManager * window);

			// Destructor
			~Event();
        private:
			
			// Constructor
			Event();
			
			// Clocking
			sf::Clock clock;
			
			// Input Stream
			std::shared_ptr<strbuf::InputStream<EventContainer>> input;
									
			//offset
			std::atomic<int> offset;

			//flags
			std::unordered_map<sf::Event::EventType, bool> flags;

			//Event Buffer
			strbuf::StreamBuffer<EventContainer> event_buffer;

			//sigleton instance
			static std::unordered_map<const jubeon::graphics::LayerManager *, std::unique_ptr<Event>> instance;

		};
	}

}


#endif
