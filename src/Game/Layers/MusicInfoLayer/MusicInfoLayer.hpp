#pragma once


#ifndef JUBEAT_ONLINE_MUSICINFOLAYER_HPP
#define JUBEAT_ONLINE_MUSICINFOLAYER_HPP

#include "../../../graphics/layer/LayerBase/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace game {
		namespace layers {
			class MusicInfoLayer : public jubeat_online::graphics::layer::LayerBase {
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