#pragma once

#ifndef jubeon_SEQUENCE_PLAYER_HPP
#define jubeon_SEQUENCE_PLAYER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "../../Graphics/Layer/LayerBase.hpp"

#include "../Sequence.hpp"
#include "../Music.hpp"
#include "../PlayRecord.hpp"

#include "../Marker.hpp"
#include "../PanelPosition.hpp"

#include <map>

namespace jubeon {
	namespace game {
		namespace layers {


			class SequencePlayer : public jubeon::graphics::LayerBase {
			public:

				SequencePlayer(
					std::shared_ptr<jubeon::game::Sequence> sequence,
					std::shared_ptr<jubeon::game::Music> music,
					std::shared_ptr<const jubeon::game::PlayRecord> playrecord,
					std::shared_ptr<jubeon::game::PanelPosition> panel_position,
					int offset_ms
					);
				
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

			private:

				const std::shared_ptr<jubeon::game::Sequence> sequence;
				const std::shared_ptr<jubeon::game::Music> music;
				const std::shared_ptr<const jubeon::game::PlayRecord> playrecord;
				const std::shared_ptr<PanelPosition> panel_position;


				//描写するオフセットms
				int offset_ms;

				//TEMPORARY
				std::shared_ptr<Marker> mk;


			};
		}
	}
}

#endif