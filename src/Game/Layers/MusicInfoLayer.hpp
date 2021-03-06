///////////////////////////////////////////////
// (c) 2016 white MusicInfoLayer.hpp
///////////////////////////////////////////////

#pragma once

#ifndef JUBEON_MUSICINFOLAYER_HPP
#define JUBEON_MUSICINFOLAYER_HPP

//for LayerBase
#include "Graphics/Layer/LayerBase.hpp"

//for std::shared_ptr
#include <memory>

//for texture
#include <SFML/Graphics.hpp>

//for music
#include "Game/Music.hpp"


namespace jubeon {
	namespace game {
		namespace layers {
			class MusicInfoLayer : public jubeon::graphics::LayerBase {
			private:

				const std::shared_ptr<game::Music> music;
				
				sf::Texture difficulty_tex;
				sf::Texture level_string_tex;
				sf::Texture level_numeric_tex;

			public:

				MusicInfoLayer(const std::shared_ptr<game::Music> & music);


				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif