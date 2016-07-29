#pragma once

#ifndef JUBEAT_ONLINE_GAME_JUDGEDEFINITION_HPP
#define JUBEAT_ONLINE_GAME_JUDGEDEFINITION_HPP

namespace jubeat_online {
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