//////////////////////////////////////////////
// (c) 2016 white PushframeLayer.hpp
//////////////////////////////////////////////

#pragma once

#ifndef JUBEON_FRAME_LAYER_HPP
#define JUBEON_FRAME_LAYER_HPP

//for LayerBase
#include "Graphics/Layer/LayerBase.hpp"

//for std::shared_ptr
#include <memory>

//for texture
#include <SFML/Graphics.hpp>

//for PlayRecord
#include "Game/PlayRecord.hpp"

//for PanelPosition
#include "Game/PanelPosition.hpp"

//for Music
#include "Game/Music.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class PushframeLayer : public jubeon::graphics::LayerBase {
			public:
				PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music);	//�V�K�v���C�p
				PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music, const std::shared_ptr<PlayRecord> & playrecord);

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				//�����ꂽ�Ƃ�
				void setPushing(unsigned char panel_no) { pushing |= (0x00000001 << panel_no); }
				
				//�������Ƃ�
				void setReleasing(unsigned char panel_no) { pushing &= (~(0x00000001 << panel_no)); }


			private:

				const std::shared_ptr<PlayRecord> playrecord;
				const std::shared_ptr<PanelPosition> panelposition;
				const std::shared_ptr<Music> music;

				//�ǂ̃}�[�J�[�������ꂽ�܂܂�
				unsigned int pushing;
				bool isPushing(unsigned char panel_no) { return (pushing & (0x00000001 << panel_no)) > 0; }

				//�O�񒲍���������
				int before_check_ms;
			};
		}
	}
}

#endif