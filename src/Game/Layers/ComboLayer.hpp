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

				//描写の時に使いそうな...
				int combo_buf;
				char combo_buff;

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
				void restart();

				//時間に応じて座標を上下する処理
				void set_Coordinates();


				ComboLayer();
				~ComboLayer();
			
			};
		}
	}
}

#endif