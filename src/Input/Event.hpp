///////////////////////////////////////////////////
// (c) 2016 white
//
//   *** REBUILDING LISTENPANEL CLASS ***
//
///////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_INPUT_EVENT_HPP
#define JUBEON_INPUT_EVENT_HPP

#include "strbuf/strbuf.hpp"

#include "SFML/Graphics.hpp"

namespace jubeon {
	namespace input {
		template<typename T>
		class EventBase {
		protected:
			std::shared_ptr<strbuf::InputStream<T>> pinput_que;
			strbuf::StreamBuffer<T> pinput_sb;

		public:
			EventBase() : pinput_que(new strbuf::InputStream<T>()) {};
			virtual ~EventBase() {}

			//Music * music;
			virtual void pollEvent(sf::Event e) = 0;
			
			virtual strbuf::StreamBuffer<T> * getPanelStreamBuf(void) {
				return this->pinput_que.get();
			}

		};
	};
};

#endif