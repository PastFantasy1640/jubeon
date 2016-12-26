#pragma once

#ifndef JUBEON_GAME_LAYER_SCORELAYER_HPP
#define JUBEON_GAME_LAYER_SCORELAYER_HPP

#include <memory>

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>

#include "Game/Player.hpp"
#include "Game/Music.hpp"
#include "Game/JudgedPanelInput.hpp"
#include "Game/Sequence.hpp"
#include "Game/MusicBar.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class ScoreLayer : public jubeon::graphics::LayerBase {
			private:

				Player *const player;
				Music *const music;

				MusicBar musicbar;


				sf::Sprite start_sp;
				sf::Sprite end_sp;
				sf::Sprite bpm_sp;
				sf::Sprite bpm_string_sp;
				sf::Sprite gray_chip_sp;
				sf::Sprite blue_chip_sp;
				sf::Sprite yellow_chip_sp;
				sf::Sprite seek_sp;

				sf::Text play_name;

				unsigned int music_length;

				ScoreLayer();
				
			public:
				ScoreLayer(Player *const player, Music *const music);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;
			};
		}
	}
}

#endif