#pragma once

#ifndef jubeon_FRAME_LAYER_HPP
#define jubeon_FRAME_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		namespace layers {
			class FrameLayer : public jubeon::graphics::LayerBase {
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