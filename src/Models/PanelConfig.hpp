#pragma once

#ifndef JUBEAT_ONLINE_PANEL_CONFIG_HPP_
#define JUBEAT_ONLINE_PANEL_CONFIG_HPP_

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ModelBase.hpp"

namespace jubeon {
	namespace models {

		/// <summary>パネル関係の設定を格納するクラス</summary>
		class PanelConfig : public ModelBase{
		public:

			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2
			};

			virtual bool Init(picojson::value val) override;
			virtual picojson::value GetJsonValue() override;

			/// <summary>HIDのIDを取得する。キーボードの場合-1を、Joystickの場合0～7を返す</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>ID</returns>
			int getHidID(const unsigned int p_index) const;

			/// <summary>キーコードを取得する。</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>sf::Keyboard::Key型のキーコード</returns>
			sf::Keyboard::Key getKeyCode(const unsigned int p_index) const;

			/// <summary>ジョイスティックのコードを取得する。キーボードの場合-1を、Joystickの場合0～7を返す</summary>
			/// <param name='p_index'>パネル番号</param>
			/// <returns>整数型コード</returns>
			int getJoystickCode(const unsigned int p_index) const;

			void setInstance(std::shared_ptr<PanelConfig> ptr);
			static PanelConfig * getInstance();

		private:
			
			static std::shared_ptr<PanelConfig> instance;

			int hid_id_[16];
			sf::Keyboard::Key key_code_[16];
			int joystick_code_[16];
		};
	}
}

#endif