#pragma once

#ifndef JUBEON_GAME_LAYER_HOLDLAYER_HPP
#define JUBEON_GAME_LAYER_HOLDLAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#include "Game/Player.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class HoldLayer : public jubeon::graphics::LayerBase {
			private:
				std::vector<sf::Texture> arrow_tex;
				std::vector<sf::Texture> panel_tex;
				sf::Texture line_tex;
				sf::Texture holdto_tex;

				Player * player;

				HoldLayer();
			public:
				HoldLayer(Player *const player);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif