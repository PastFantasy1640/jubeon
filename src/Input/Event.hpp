///////////////////////////////////////////////////
// (c) 2016 white
//
//   *** REBUILDING LISTENPANEL CLASS ***
//
///////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_INPUT_EVENT_HPP
#define JUBEON_INPUT_EVENT_HPP
/*
//Mutex
#include <mutex>

//list
#include <list>

#include <SFML/Graphics.hpp>

#include <vector>

namespace jubeon {
	namespace input {


		class Event {
		public:

			Event(sf::Window * layermanager);
			virtual ~Event();

			//std::bind(std::mem_fn(&Foo::Do), &foo);
			void setCallback(Callback function);
			void run(void);

			static bool getInstance(const sf::Window * layermanager, Event * dst);
		private:

			Event();

			sf::Window * window;

			Callback cb;

			std::mutex mtx;

			static std::vector<Event *> events;
		};
	}
}

*/


/*
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

            static c

			void process(jubeon::graphics::LayerManager * main_window);

			const unsigned int getTimerCount() const;
			

			using strbuf::StreamBuffer<EventContainer>::addOutputStream;

			E
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
			//std::atomic<int> offset;

			//flags
			std::unordered_map<sf::Event::EventType, bool> flags;

			//Event Buffer
			strbuf::StreamBuffer<EventContainer> event_buffer;

			//sigleton instance
			static std::unordered_map<const jubeon::graphics::LayerManager *, std::unique_ptr<Event>> instance;

		};
	}

}
*/

#endif
