
#include "Panelconfig.hpp"
#include "Systems/Exceptions.hpp"
#include "Systems/picojson_util.hpp"

#include "Systems/Logger.hpp"

std::shared_ptr<jubeon::models::PanelConfig> jubeon::models::PanelConfig::instance;

int jubeon::models::PanelConfig::getHidID(const unsigned int p_index) const{
	if (p_index > 15) throw jubeon::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return hid_id_[p_index];
}

sf::Keyboard::Key jubeon::models::PanelConfig::getKeyCode(const unsigned int p_index) const{
	if (p_index > 15) throw jubeon::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return key_code_[p_index];
}

int jubeon::models::PanelConfig::getJoystickCode(const unsigned int p_index) const{
	if (p_index > 15) throw jubeon::systems::exceptions::panel_out_of_index("Panel Index Out of Range.");
	return joystick_code_[p_index];
}

bool jubeon::models::PanelConfig::Init(picojson::value val)
{
	try {
		//TO DO : throw文
		if (!val.is<picojson::object>()) throw "hoge";

		auto root = val.get<picojson::object>();

		if (!picojson_util::has_field<picojson::array>(val, "keyconfig")) throw "hoge";

		auto keyconfigs = root["keyconfig"].get<picojson::array>();
		
		if (keyconfigs.size() != 16) throw "hoge";
		for (auto p : keyconfigs) {
			//それぞれで2つの値があるか
			if (p.get<picojson::array>().size() != 2) throw "hoge";
		}
		

		//大丈夫らしい
		for (int i = 0; i < keyconfigs.size(); i++) {
			auto key = keyconfigs[i].get<picojson::array>();
			if (key[0].get<double>() == 0) {
				//キーボード
				this->key_code_[i] = static_cast<sf::Keyboard::Key>(static_cast<int>(key[1].get<double>()));
				this->hid_id_[i] = -1;
			}
			else {
				this->joystick_code_[i] = static_cast<int>(key[1].get<double>());
				this->hid_id_[i] = static_cast<int>(key[0].get<double>()) - 1;
			}
		}
	}
	catch (std::string e) {
		systems::Logger::error("keyconfigのjsonに誤りがあります。");
		return false;
	}

	return true;
}

picojson::value jubeon::models::PanelConfig::GetJsonValue()
{
	//TO DO : 設定の書き出し
	return picojson::value();
}

void jubeon::models::PanelConfig::setInstance(std::shared_ptr<PanelConfig> ptr)
{
	if(!instance) instance = ptr;
}

jubeon::models::PanelConfig * jubeon::models::PanelConfig::getInstance()
{
	if (!instance) {
		instance.reset(new PanelConfig);
	}

	return instance.get();
}
