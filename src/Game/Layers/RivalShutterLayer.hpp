////////////////////////////////////////////////
// (c) 2016 white RivalShutterLayer.hpp
////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_GAME_LAYER_RIVALSHUTTERLAYER_HPP
#define JUBEON_GAME_LAYER_RIVALSHUTTERLAYER_HPP

#include <memory>

#include "Graphics/Layer/LayerBase.hpp"

#include "Game/Music.hpp"

#include "Game/DifficultyDefinition.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class RivalShutterLayer : public jubeon::graphics::LayerBase {
			public:

				RivalShutterLayer(const sf::Vector2f position ,const std::shared_ptr<Music> & music, const Difficulty & difficulty);
				RivalShutterLayer(const sf::Vector2f position);	//enable : false

				virtual void Init() override;
				virtual void Exit() override;
				virtual void Draw() override;

			private:
				const std::shared_ptr<Music> music;
				const Difficulty difficulty;
				const bool enable;
			};
		};
	};
};

#endif
