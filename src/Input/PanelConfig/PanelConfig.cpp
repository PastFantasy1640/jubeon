
#include "Panelconfig.hpp"

#include <iostream>

#include "../../systems/INIFileReader/INIFileReader.hpp"
#include "../../systems/exceptions/Exceptions.hpp"

int					jubeat_online::config::Panel::hid_id_[16]			= { -1 } ;
sf::Keyboard::Key	jubeat_online::config::Panel::key_code_[16]			= { sf::Keyboard::Key::A };
int					jubeat_online::config::Panel::joystick_code_[16]	= { 0 };

int jubeat_online::config::Panel::set(const std::string fpath) {	

	//iniファイル読み込み
	wg::systems::INIFileReader setting;
	setting.load(fpath);


	for (int i = 0; i < 16; i++) {
		std::string str = setting.get("config", "panel" + std::to_string(i + 1), "0," + std::to_string(i));
		int pid = std::stoi(str.substr(0));
		if (pid >= 0 && pid <= 8) {
			hid_id_[i] = pid-1;
		}
		else {
			//エラー（該当しない）
			return Result::INVALID_CONFIG_CONTROLER_ID;
		}

		int k = std::stoi(str.substr(2));

		if (hid_id_[i] == -1) {
			if (k >= 0 && k < sf::Keyboard::KeyCount) key_code_[i] = static_cast<sf::Keyboard::Key>(std::stoi(str.substr(2)));
			else return Result::INVALID_CONFIG_KEYBOARD_NUM;
		}
		else {
			joystick_code_[i] = k;
		}
	}


	return Result::SUCCESS;
}

int jubeat_online::config::Panel::getHidID(const unsigned int p_index) {
	if (p_index > 15) throw jubeat_online::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return hid_id_[p_index];
}

sf::Keyboard::Key jubeat_online::config::Panel::getKeyCode(const unsigned int p_index) {
	if (p_index > 15) throw jubeat_online::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return key_code_[p_index];
}

int jubeat_online::config::Panel::getJoystickCode(const unsigned int p_index) {
	if (p_index > 15) throw jubeat_online::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return joystick_code_[p_index];
}