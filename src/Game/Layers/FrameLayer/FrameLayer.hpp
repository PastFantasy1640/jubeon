#pragma once

#ifndef JUBEAT_ONLINE_FRAME_LAYER_HPP
#define JUBEAT_ONLINE_FRAME_LAYER_HPP

#include "../../../graphics/layer/LayerBase/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace game {
		namespace layers {
			class FrameLayer : public jubeat_online::graphics::layer::LayerBase {
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