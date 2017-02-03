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

				//sf;;clock的なのに修正しなきゃ
				clock_t t0;//最初に記録
				clock_t t1;//次に記録
				clock_t t_;//時間の差

				//描写の時に使いそうな...
				int combo_baf;
				char combo_baff;

				//描写用の座標
				int y;
				int x1, x2, x3, x4;

				//初期のy座標
				int y_def;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				//値変更の検知フラグを見て、リスタート処理
				void Restart();

				//時間に応じて座標を上下する処理
				void Set_Coordinates();
			
			};
		}
	}
}

#endif