#pragma once

#ifndef jubeon_COMBO_LAYER_HPP
#define jubeon_COMBO_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Combo.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class ComboLayer : public jubeon::graphics::LayerBase {
			private:
				sf::Texture dummy;

				Combo combo;

				//sf;;clock�I�Ȃ̂ɏC�����Ȃ���
				clock_t t0;//�ŏ��ɋL�^
				clock_t t1;//���ɋL�^
				clock_t t_;//���Ԃ̍�

				//�`�ʂ̎��Ɏg��������...
				int combo_baf;
				char combo_baff;

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
				void Restart();

				//���Ԃɉ����č��W���㉺���鏈��
				void Set_Coordinates();
			
			};
		}
	}
}

#endif