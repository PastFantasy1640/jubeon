#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_PLAYER_HPP
#define JUBEAT_ONLINE_SEQUENCE_PLAYER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "../../Graphics/Layer/LayerBase.hpp"

#include "../Sequence.hpp"
#include "../Music.hpp"
#include "../PlayRecord.hpp"

#include "../Marker.hpp"

namespace jubeat_online{
	namespace game {
		namespace layers {
			class SequencePlayer : public jubeat_online::graphics::layer::LayerBase {
			public:

				SequencePlayer(const Sequence * sequence, const Music * music, std::unique_ptr<PlayRecord> playrecord);

				void process(void);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

			private:
				const Sequence * sequence;
				const Music * music;
				std::unique_ptr<PlayRecord> playrecord;

				//どのマーカーが押されたままか
				unsigned int pushing;
				bool isPushing(unsigned char panel_no) { return (pushing & (0x00000001 << panel_no)); }
				void setPushing(unsigned char panel_no) { pushing |= (0x00000001 << panel_no); }
				void setReleasing(unsigned char panel_no) { pushing &= (~(0x00000001 << panel_no)); }

				//前回調査した時間
				unsigned int before_check_ms;

				sf::Texture panel_frame;

				//TEMPORARY
				Marker mk;

			};
		}
	}
}

#endif