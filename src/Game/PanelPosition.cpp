#include "PanelPosition.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"

jubeon::game::PanelPosition::PanelPosition(const std::string json_file)
	: ModelBase(json_file)
{
	for (auto p : this->panel_rect) p = sf::IntRect(0, 0, 100, 100);
}

const sf::IntRect & jubeon::game::PanelPosition::get(unsigned char panel_no) const
{
	return this->panel_rect.at(panel_no);
}

bool jubeon::game::PanelPosition::set(void)
{

	for (int i = 0; i < 16; i++) {
		this->panel_rect[i].left = static_cast<int>(this->getJson()["panel_position"][i][0].num());
		this->panel_rect[i].top = static_cast<int>(this->getJson()["panel_position"][i][1].num());
		this->panel_rect[i].width = static_cast<int>(this->getJson()["panel_position"][i][2].num());
		this->panel_rect[i].height = static_cast<int>(this->getJson()["panel_position"][i][3].num());
	}
	return true;
}

void jubeon::game::PanelPosition::set(const std::array<sf::IntRect, 16>& value)
{
	for (int i = 0; i < value.size(); i++) {
		this->panel_rect[i] = value[i];
	}
}

float jubeon::game::PanelPosition::get_ex(int origin, int to)
{
	return static_cast<float>(to) / static_cast<float>(origin);
}
