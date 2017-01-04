#pragma once

#ifndef JUBEON_GAME_LAYER_HOLDLAYER_HPP
#define JUBEON_GAME_LAYER_HOLDLAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		namespace layers {
			class HoldLayer : public jubeon::graphics::LayerBase {
			private:
				//sf::Texture frame;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif