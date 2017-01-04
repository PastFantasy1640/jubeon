#pragma once

#ifndef JUBEON_GAME_LAYER_HOLDLAYER_HPP
#define JUBEON_GAME_LAYER_HOLDLAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#include "Game/Player.hpp"
#include "Game/PanelPosition.hpp"
#include "Game/Music.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class HoldLayer : public jubeon::graphics::LayerBase {
			private:
				std::vector<sf::Texture> arrow_tex;
				std::vector<sf::Texture> panel_tex;
				sf::Texture line_tex;
				sf::Texture holdto_tex;

				Player *const player;
				const PanelPosition ppos;
				const Music * music;

				HoldLayer();

				void _holdtoDraw();

			public:
				HoldLayer(Player *const player, const PanelPosition & panel_position, const Music * music);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif