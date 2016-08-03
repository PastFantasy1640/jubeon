#pragma once


#ifndef jubeon_MUSICINFOLAYER_HPP
#define jubeon_MUSICINFOLAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace jubeon {
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