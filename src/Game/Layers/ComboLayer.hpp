#pragma once

#ifndef jubeon_COMBO_LAYER_HPP
#define jubeon_COMBO_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Combo.hpp"
#include "../../Game/PanelPosition.hpp"
#include <SFML/System/Clock.hpp>
#include <array>

namespace jubeon {
			class ComboLayer : public jubeon::graphics::LayerBase {
			private:
				//sf::Texture dummy;

				const Combo * combo;
				const PanelPosition * panel_position;

				sf::Sprite combo_sp[10];

				sf::Clock clock;
				int t;
				int no = 0;
				int n = 0; //���W�L�^�i���o�[�J�E���g�p

				float y_[32]; //���W�L���p�ϐ�

				//�`�ʔ͈�
				float w;

				//�������p�̕ϐ�
				char combo_buf[4];
				int keta1;
				int keta2;
				int keta3;
				int keta4;

				//�`�ʗp�̍��W
				float y;

				//������y���W
				float y_def;

				//�R���{�摜��Weight
				float combo_w;

				//�g�嗦�H
				float scale;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				ComboLayer(const Combo * combo, const PanelPosition * panel_position);

				//�l�ύX�̌��m�t���O�����āA���X�^�[�g����
				void restart();

				//���Ԃɉ����č��W���㉺���鏈��
				float get_Coordinates();

				~ComboLayer();

			};
		}

#endif