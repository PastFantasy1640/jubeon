#include "PanelPosition.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"

jubeon::game::PanelPosition::PanelPosition(const std::string json_file)
	: ModelBase(json_file)
{
	this->bounding_box = sf::IntRect(0, 0, 100, 100);
	this->push_back(sf::IntRect(0, 0, 100, 100));
}

jubeon::game::PanelPosition::PanelPosition(const PanelPosition & copy)
	: ModelBase(copy.getFilename()), std::vector<sf::IntRect>(copy), bounding_box(copy.bounding_box)
{
}
/*
const sf::IntRect & jubeon::game::PanelPosition::get(unsigned char panel_no) const
{
	return this->panel_rect.at(panel_no);
}*/

bool jubeon::game::PanelPosition::set(void)
{
	this->clear();
	for (int i = 0; i < this->getJson()["panel_position"].size(); i++) {
		this->push_back(sf::IntRect(
			static_cast<int>(this->getJson()["panel_position"][i][0].num()),
			static_cast<int>(this->getJson()["panel_position"][i][1].num()),
			static_cast<int>(this->getJson()["panel_position"][i][2].num()),
			static_cast<int>(this->getJson()["panel_position"][i][3].num())));
	}

	try {
		int min_x = this->at(0).left, max_x = this->at(0).left + this->at(0).width, min_y = this->at(0).top, max_y = this->at(0).top + this->at(0).height; //position

		for (auto p = ++this->begin(); p != this->end(); p++) {
			if (p->left < min_x) min_x = p->left;
			else if (max_x < (p->left + p->width)) max_x = p->left + p->width;

			if (p->top < min_y) min_y = p->top;
			else if (max_y < (p->top + p->height)) max_y = p->top + p->height;
		}

		this->bounding_box.left = min_x;
		this->bounding_box.top = min_y;
		this->bounding_box.width = max_x - min_x;
		this->bounding_box.height = max_y - min_y;

	}
	catch (std::out_of_range & e) {
		return false;
	}

	return true;
}

sf::IntRect jubeon::game::PanelPosition::get(std::size_t index) const
{

	if (index < this->size()) 	return this->at(index);

	throw OutOfRangePanelNumberException(index);

	return sf::IntRect();
}

sf::IntRect jubeon::game::PanelPosition::getBoundingBox(void) const
{
	return this->bounding_box;
}
/*
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
*/