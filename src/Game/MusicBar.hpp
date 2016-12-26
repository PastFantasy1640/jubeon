#pragma once

#ifndef JUBEON_GAME_MUSICBAR_HPP
#define JUBEON_GAME_MUSICBAR_HPP

#include <array>

#include "Sequence.hpp"
#include "Music.hpp"

namespace jubeon {
	namespace game {

		struct Bar {
			unsigned int num;
			enum Result { YELLOW, BLUE, GRAY, NJDGE } result;
			unsigned int ms;
		};

		static const size_t BAR_SIZE = 120;

		class MusicBar : protected std::array<Bar, BAR_SIZE>{
		public:
			
			MusicBar();

			void init(const Sequence * sequence, const Music * music);

			void update(const Music * music);

			using std::array<Bar, BAR_SIZE>::const_iterator;
			using std::array<Bar, BAR_SIZE>::begin;
			using std::array<Bar, BAR_SIZE>::end;
			using std::array<Bar, BAR_SIZE>::operator[];
			using std::array<Bar, BAR_SIZE>::at;

			std::array<Bar, BAR_SIZE>::const_iterator search(const int ms);

		private:

			unsigned int before_check_ms;
			const Sequence * sequence;

		};
	};
};

#endif