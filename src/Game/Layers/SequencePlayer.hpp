#pragma once

#ifndef jubeon_SEQUENCE_PLAYER_HPP
#define jubeon_SEQUENCE_PLAYER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "../../Graphics/Layer/LayerBase.hpp"

#include "../Sequence.hpp"
#include "../Music.hpp"
#include "../PlayRecord.hpp"
#include "../Player.hpp"

#include "../Marker.hpp"
#include "../PanelPosition.hpp"

#include <map>

namespace jubeon {
	namespace game {
		namespace layers {


			class SequencePlayer : public jubeon::graphics::LayerBase {
			public:

				SequencePlayer(
					const Sequence * sequence,
					const Music * music,
					const Player * player,
					const PanelPosition * panel_position,
					int offset_ms
					);
				
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

			private:

				const Sequence * sequence;
				const jubeon::game::Music * music;
				const Player * player;
				const PanelPosition * panel_position;


				//描写するオフセットms
				int offset_ms;

				//TEMPORARY
				std::shared_ptr<Marker> mk;


			};
		}
	}
}

#endif