#pragma once

#ifndef TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP
#define TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP

#include <memory>

#include "../../../graphics/layer/LayerBase/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../../Theme/Drop.hpp"

namespace jubeat_online {
	namespace game {
		namespace layers {
			class BackgroundLayer : public jubeat_online::graphics::layer::LayerBase{
			private:
				sf::Texture background;

				std::unique_ptr<Theme::Drop<5>> drop1;
				std::unique_ptr<Theme::Drop<5>> drop2;

			public:
				BackgroundLayer();
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				template<std::size_t S>
				static std::array<sf::Vector2f, S> genRandomPoints(unsigned int r);
			};
		}
	}
}


#endif

