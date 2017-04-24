#pragma once

#ifndef JUBEON_GAME_PANELPOSITION_HPP
#define JUBEON_GAME_PANELPOSITION_HPP

#include "Models/ModelBase.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#include <exception>

namespace jubeon {
	namespace game {
		
		class OutOfRangePanelNumberException : public std::out_of_range {
		public:
			OutOfRangePanelNumberException(const int number) throw () : std::out_of_range("Panel Number is Out of range. Number is " + std::to_string(number) + ".") {}
		};

		class PanelPositionNotInitializedException : public std::out_of_range {
		public:
			PanelPositionNotInitializedException() throw () : std::out_of_range("0 Panel Number is not existing.") {}
		};

		class PanelPosition : public jubeon::models::ModelBase, protected std::vector<sf::IntRect>{
		public:

			/** jsonファイル読み込みコンストラクタ
			 * jsonファイルからパネルポジションを指定します。
			 * もしも解析が上手く行かなかった場合、デフォルトの配置を保持します。
			 * @param json_file jsonファイルのファイル名を指定します。
			 */
			PanelPosition(const std::string json_file);
			
			/** コピーコンストラクタ
			 * コピーによるコンストラクタ
			 * @param copy コピー元のインスタンス
			 */
			PanelPosition(const PanelPosition & copy);

			/** デコンストラクタ
			 */
			~PanelPosition();

			/** ModelBaseのオーバーライド関数
			 */
			virtual bool set() override;

			using std::vector<sf::IntRect>::at;
			using std::vector<sf::IntRect>::operator[];
			using std::vector<sf::IntRect>::size;

			/** PanelPosition::getBoundingBox関数
			 * 全体の左上座標と高さ幅を返します。
			 * @returns sf::IntRect型。左上座標と高さ幅を持ったコピーを返します。
			 */
			sf::IntRect getBoundingBox(void) const;



			//void set(const std::array<sf::IntRect, 16> & value);

			//static float get_ex(int origin, int to);

			

			//const sf::IntRect & get(unsigned char panel_no) const;


		private:
			PanelPosition();

			sf::IntRect bounding_box;
						
		};
	}
}

#endif