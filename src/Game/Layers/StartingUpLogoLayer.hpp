#pragma once

#ifndef JUBEON_GAME_LAYERS_STARTINGUPLOGOLAYER_HPP
#define JUBEON_GAME_LAYERS_STARTINGUPLOGOLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Graphics/Layer/LayerBase.hpp"
#include "../Scenes/StartingUpScene.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class StartingUpLogoLayer : public jubeon::graphics::LayerBase {
			private:
				sf::Texture logo;
				jubeon::game::scenes::StartingUpScene * scene;


			public:
				StartingUpLogoLayer(jubeon::game::scenes::StartingUpScene * scene);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif