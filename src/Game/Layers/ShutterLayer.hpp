#pragma once

#ifndef jubeon_SHUTTER_LAYER_HPP
#define jubeon_SHUTTER_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		namespace layers {
			class ShutterLayer : public jubeon::graphics::LayerBase {
			private:
				sf::Texture dummy;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif