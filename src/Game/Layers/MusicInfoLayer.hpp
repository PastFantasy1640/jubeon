#pragma once


#ifndef JUBEAT_ONLINE_MUSICINFOLAYER_HPP
#define JUBEAT_ONLINE_MUSICINFOLAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace game {
		namespace layers {
			class MusicInfoLayer : public jubeon::graphics::LayerBase {
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