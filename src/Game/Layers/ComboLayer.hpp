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
				int t_; //y���p�v�Z�p�^�C���ϐ�
				int no_ = 0; //�L�^�I���t���O
				int n_ = 0; //���W�L�^�i���o�[�J�E���g�p

				float y_[32]; //���W�L���p�ϐ��z��

				//�`�ʔ͈�
				float w_;

				//�������p�̕ϐ�
				char combo_buf_[4];
				int keta1_;
				int keta2_;
				int keta3_;
				int keta4_;

				//�`�ʗp�̍��W
				float y_draw_;

				//������y���W
				float y_def_;

				//�R���{�摜��Weight
				float combo_w_;

				//�g�嗦�H
				float scale_;

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