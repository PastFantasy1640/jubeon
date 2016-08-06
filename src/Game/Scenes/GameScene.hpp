#pragma once

#ifndef JUBEON_GAME_SCENES_GAMESCENE_HPP
#define JUBEON_GAME_SCENES_GAMESCENE_HPP

#include "Systems/Scene.hpp"
#include <SFML/Graphics.hpp>

//for Notes
#include "Game/Sequence.hpp"
#include "Game/Music.hpp"
#include "Game/PlayRecord.hpp"

namespace jubeon {
	namespace game {
		namespace scenes {
			class GameScene : public jubeon::systems::Scene{
			public:
				bool isinited = false;
				void init();
				
				std::shared_ptr<Sequence> sequence;
				std::shared_ptr<PlayRecord> playrecord;
				std::shared_ptr<Music> music;


				virtual int process(void) override;
			};
		};
	};
};

#endif