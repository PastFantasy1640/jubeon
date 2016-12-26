////////////////////////////////////////////
// (c) 2016  white   WindowsConfig.cpp
////////////////////////////////////////////

#include "WindowConfig.hpp"
#include "Systems/Logger.hpp"


jubeon::models::WindowConfig::WindowConfig(const std::string filename)
	: ModelBase(filename),
	layoutType(graphics::LayerManager::LayoutType::Y_PLUS),
	size(sf::Vector2f(0, 0)),
	position(sf::Vector2f(0, 0)),
	vsyncEnabled(true)
{
}

sf::Vector2i jubeon::models::WindowConfig::getSize() const
{
	return this->size;
}

sf::Vector2i jubeon::models::WindowConfig::getPosition() const
{
	return this->position;
}

bool jubeon::models::WindowConfig::getVsyncEnabled() const
{
	return this->vsyncEnabled;
}

jubeon::graphics::LayerManager::LayoutType jubeon::models::WindowConfig::getLayoutType() const
{
	return this->layoutType;
}

bool jubeon::models::WindowConfig::set()
{

	if (this->getJson()["layout_type"].str() == "vertical_x+") this->layoutType = graphics::LayerManager::LayoutType::X_PLUS;
	else if (this->getJson()["layout_type"].str() == "vertical_y-") this->layoutType = graphics::LayerManager::LayoutType::Y_MINUS;
	else if (this->getJson()["layout_type"].str() == "vertical_x-") this->layoutType = graphics::LayerManager::LayoutType::X_MINUS;
	
	this->size.x = this->getJson()["size"]["width"].num();
	this->size.y = this->getJson()["size"]["height"].num();
	this->position.x = this->getJson()["position"]["x"].num();
	this->position.y = this->getJson()["position"]["y"].num();

	this->vsyncEnabled = this->getJson()["vsync_enabled"].is();

	return true;
}


