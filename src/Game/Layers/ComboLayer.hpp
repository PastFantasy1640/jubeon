#pragma once

#ifndef jubeon_COMBO_LAYER_HPP
#define jubeon_COMBO_LAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Combo.hpp"
#include <SFML/System/Clock.hpp>
#include <array>

namespace jubeon {
	namespace game {
		namespace layers {
			class ComboLayer : public jubeon::graphics::LayerBase {
			private:
				sf::Texture dummy;

				Combo * combo;
				ComboLayer::ComboLayer(Combo * combo) : combo(combo) {}


				sf::Sprite combo_sp[10];

				/*sf::Sprite combo0_sp;
				sf::Sprite combo1_sp;
				sf::Sprite combo2_sp;
				sf::Sprite combo3_sp;
				sf::Sprite combo4_sp;
				sf::Sprite combo5_sp;
				sf::Sprite combo6_sp;
				sf::Sprite combo7_sp;
				sf::Sprite combo8_sp;
				sf::Sprite combo9_sp;*/

				sf::Clock clock;
				int t;


				//描写の時に使いそうな...

				float w; //描写範囲

				//int combo_buf;
				char combo_buf[4];
				int keta1;
				int keta2;
				int keta3;
				int keta4;


				//描写用の座標
				float y;

				//初期のy座標
				float y_def;

			public:
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				//値変更の検知フラグを見て、リスタート処理
				void restart();

				//時間に応じて座標を上下する処理
				float get_Coordinates();


				ComboLayer(float m);
				~ComboLayer();
			
			};
		}
	}
}

#endif