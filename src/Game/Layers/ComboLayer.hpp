#pragma once

#ifndef jubeon_COMBO_LAYER_HPP
#define jubeon_COMBO_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Combo.hpp"
#include <SFML/System/Clock.hpp>

namespace jubeon {
	namespace game {
		namespace layers {
			class ComboLayer : public jubeon::graphics::LayerBase {
			private:
				sf::Texture dummy;

				Combo * combo;
				ComboLayer::ComboLayer(Combo * combo) : combo(combo) {}


				sf::Clock clock;
				int t;

				//�`�ʂ̎��Ɏg��������...
				int combo_buf;
				char combo_buff;

				//�`�ʗp�̍��W
				int y;
				int x1, x2, x3, x4;

				//������y���W
				int y_def;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				//�l�ύX�̌��m�t���O�����āA���X�^�[�g����
				void restart();

				//���Ԃɉ����č��W���㉺���鏈��
				void set_Coordinates();


				ComboLayer();
				~ComboLayer();
			
			};
		}
	}
}

#endif