#pragma once

#ifndef JUBEAT_ONLINE_PANEL_CONFIG_HPP_
#define JUBEAT_ONLINE_PANEL_CONFIG_HPP_

#include <string>
#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace config {

		/// <summary>パネル関係の設定を格納するクラス</summary>
		class Panel {
		public:

			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2
			};

			/// <summary>設定ファイルの読み出し。0以外なら読み込みは失敗し、途中で作業を中断しています。</summary>
			/// <param name='fpath'>読みだすINIファイルパス</param>
			/// <returns>実行結果。0なら正常、それ以外はエラーコードを返す</returns>
			static int set(const std::string fpath);

			/// <summary>HIDのIDを取得する。キーボードの場合-1を、Joystickの場合0～7を返す</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>ID</returns>
			static int getHidID(const unsigned int p_index);

			/// <summary>キーコードを取得する。</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>sf::Keyboard::Key型のキーコード</returns>
			static sf::Keyboard::Key getKeyCode(const unsigned int p_index);

			/// <summary>ジョイスティックのコードを取得する。キーボードの場合-1を、Joystickの場合0～7を返す</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>整数型コード</returns>
			static int getJoystickCode(const unsigned int p_index);

		private:
			static int hid_id_[16];
			static sf::Keyboard::Key key_code_[16];
			static int joystick_code_[16];
		};
	}
}

#endif