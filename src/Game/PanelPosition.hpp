#pragma once

#ifndef JUBEON_GAME_PANELPOSITION_HPP
#define JUBEON_GAME_PANELPOSITION_HPP

#include "Models/ModelBase.hpp"
#include <SFML/Graphics.hpp>
#include <array>

namespace jubeon {
	namespace game {
		class PanelPosition : public jubeon::models::ModelBase {
		public:

			//デフォルトコンストラクタ
			PanelPosition();

			const sf::IntRect & get(unsigned char panel_no) const;

			bool loadJson(const std::string json_file);

			void set(const std::array<sf::IntRect, 16> & value);

			static float get_ex(int origin, int to);

			virtual bool Init(picojson::value val) override;

		protected:


			virtual picojson::value GetJsonValue() override;

		private:
			std::array<sf::IntRect,16> panel_rect;

		};
	}
}

#endif