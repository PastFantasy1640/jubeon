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
				int t_; //y座用計算用タイム変数
				int no_ = 0; //記録終了フラグ
				int n_ = 0; //座標記録ナンバーカウント用

				float y_[32]; //座標記憶用変数配列

				//描写範囲
				float w_;

				//桁分割用の変数
				char combo_buf_[4];
				int keta1_;
				int keta2_;
				int keta3_;
				int keta4_;

				//描写用の座標
				float y_draw_;

				//初期のy座標
				float y_def_;

				//コンボ画像のWeight
				float combo_w_;

				//拡大率？
				float scale_;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				ComboLayer(const Combo * combo, const PanelPosition * panel_position);

				//値変更の検知フラグを見て、リスタート処理
				void restart();

				//時間に応じて座標を上下する処理
				float get_Coordinates();

				~ComboLayer();

			};
		}

#endif