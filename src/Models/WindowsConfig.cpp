////////////////////////////////////////////
// (c) 2016  white   WindowsConfig.cpp
////////////////////////////////////////////

#include "WindowConfig.hpp"
#include "Systems/Logger.hpp"

jubeon::models::WindowConfig::WindowConfig(const std::string filename)
	: ModelBase(filename),
	layoutType(LayoutType::HORIZONTAL),
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

jubeon::models::WindowConfig::LayoutType jubeon::models::WindowConfig::getLayoutType() const
{
	return this->layoutType;
}

bool jubeon::models::WindowConfig::set()
{

	std::string err_str;
	auto add_err = [&err_str](std::string key, std::string str) { 
		if (!err_str.empty()) err_str += "\n";
		err_str += "[key:" + key + "]" + str; 
	};
	
	std::string layout_type = (*this->json)["layout_type"].str();
	if (this->json->isError()) add_err("layout_type", this->json->getError());

	bool vsync_enabled = (*this->json)["vsync_enabled"].is();
	if (this->json->isError()) add_err("layout_enabled", this->json->getError());

	//size
	double size_w = (*this->json)["size"]["width"].num();
	if (this->json->isError()) add_err("size.width", this->json->getError());

	double size_h = (*this->json)["size"]["height"].num();
	if (this->json->isError()) add_err("size.height", this->json->getError());

	//position
	double position_x = (*this->json)["position"]["x"].num();
	if (this->json->isError()) add_err("position.x", this->json->getError());

	double position_y = (*this->json)["position"]["y"].num();
	if (this->json->isError()) add_err("position.y", this->json->getError());


	if (layout_type == "vertical") this->layoutType = LayoutType::VERTICAL;
	else if (layout_type == "horizontal") this->layoutType = LayoutType::HORIZONTAL;

	this->vsyncEnabled = vsync_enabled;
	this->size.x = static_cast<int>(size_w);
	this->size.y = static_cast<int>(size_h);
	this->position.x = static_cast<int>(position_x);
	this->position.y = static_cast<int>(position_y);


	//errors
	if (!err_str.empty()) {
		systems::Logger::warning("Json file has some errors. ERRORS:" + err_str);
		return false;
	}

	return true;
}


