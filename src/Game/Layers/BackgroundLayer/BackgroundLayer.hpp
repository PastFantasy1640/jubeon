#pragma once

#ifndef TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP
#define TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP

#include "../../../graphics/layer/LayerBase/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace game {
		namespace layers {
			class BackgroundLayer : public jubeat_online::graphics::layer::LayerBase{
			private:
				sf::Texture background;
			
			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif