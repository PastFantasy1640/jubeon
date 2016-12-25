
#include "PanelConfig.hpp"
#include "Systems/Exceptions.hpp"
#include "Systems/picojson_util.hpp"

#include "Systems/Logger.hpp"


jubeon::models::PanelConfig::PanelConfig(const std::string filename)
	: ModelBase(filename)
{
}

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

bool jubeon::models::PanelConfig::set(void)
{
	for (int i = 0; i < 16; i++) {
		this->hid_id_[i] = static_cast<int>((*this->json)["keyconfig"][i][0].num()) - 1;
		int value = ((*this->json)["keyconfig"][i][1].num());
		if (this->hid_id_[i] == -1) this->key_code_[i] = static_cast<sf::Keyboard::Key>(value);
		else this->joystick_code_[i] = static_cast<int>(value);
	}
	return false;
}


/*
jubeon::models::PanelConfig * jubeon::models::PanelConfig::getInstance()
{
	if (!instance) {
		instance.reset(new PanelConfig("media / config / keyconfig.json"));
	}

	return instance.get();
}
*/