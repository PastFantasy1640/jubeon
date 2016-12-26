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

#include "strbuf/strbuf.hpp"

#include "Input/PanelInput.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class PushframeLayer : public jubeon::graphics::LayerBase {
			public:
				PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, strbuf::StreamBuffer<input::PanelInput> * pinput_sb );	//�V�K�v���C�p

				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				//�����ꂽ�Ƃ�
				void setPushing(unsigned char panel_no) { pushing |= (0x00000001 << panel_no); }
				
				//�������Ƃ�
				void setReleasing(unsigned char panel_no) { pushing &= (~(0x00000001 << panel_no)); }
				

				std::shared_ptr<strbuf::OutputStream<input::PanelInput>> poutput_que;


			private:

				std::shared_ptr<PanelPosition> panelposition;

				//�ǂ̃}�[�J�[�������ꂽ�܂܂�
				unsigned int pushing;
				bool isPushing(unsigned char panel_no) { return (pushing & (0x00000001 << panel_no)) > 0; }

			};
		}
	}
}

#endif