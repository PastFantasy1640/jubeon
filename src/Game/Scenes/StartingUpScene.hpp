#pragma once

#ifndef JUBEON_GAME_SCENES_STARTINGUPSCENE_HPP
#define JUBEON_GAME_SCENES_STARTINGUPSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Systems/Scene.hpp"

namespace jubeon {
	namespace game {
		namespace scenes {
			class StartingUpScene : public jubeon::systems::Scene {
			public:

				sf::Clock ck;

				virtual int process(void) override;
			};
		};
	};
};

#endif