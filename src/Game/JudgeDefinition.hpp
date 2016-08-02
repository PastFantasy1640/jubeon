#pragma once

#ifndef jubeon_GAME_JUDGEDEFINITION_HPP
#define jubeon_GAME_JUDGEDEFINITION_HPP

namespace jubeon {
	namespace game {
		enum Judge : size_t {
			PERFECT = 0,
			GREAT,
			GOOD,
			EARLY,
			LATE,
			MISS,
			NOJUDGE
		};
	}
}

#endif