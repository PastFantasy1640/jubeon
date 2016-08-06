#pragma once

#ifndef JUBEON_GAME_SCENES_GAMESCENE_HPP
#define JUBEON_GAME_SCENES_GAMESCENE_HPP

#include "Systems/Scene.hpp"
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		namespace scenes {
			class GameScene : public jubeon::systems::Scene{
			public:
				bool isinited = false;
				void init();
				virtual int process(void) override;
			};
		};
	};
};

#endif