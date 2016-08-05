#include "WindowConfig.hpp"
#include <string>
#include "Systems/picojson.hpp"
#include <iostream>

namespace jubeon { namespace models {
	bool WindowConfig::Init(picojson::value val) {
		if (!val.is<picojson::object>()) {
			return false;
		}

		auto root = val.get<picojson::object>();
		if (root.find("layout_type") == root.end()
			|| !root["layout_type"].is<std::string>()) {
			return false;
		}

		if (root.find("vsync_enabled") == root.end()
			|| !root["vsync_enabled"].is<bool>()) {
			return false;
		}

		if (root.find("size") == root.end()
			|| !root["size"].is<picojson::object>()) {
			return false;
		}
		auto size = root["size"].get<picojson::object>();
		if (size.find("width") == size.end()
			|| !size["width"].is<double>()) {
			return false;
		}
		if (size.find("height") == size.end()
			|| !size["height"].is<double>()) {
			return false;
		}

		if (root.find("position") == root.end()
			|| !root["position"].is<picojson::object>()) {
			return false;
		}
		auto position = root["position"].get<picojson::object>();
		if (position.find("x") == position.end()
			|| !position["x"].is<double>()) {
			return false;
		}
		if (position.find("y") == position.end()
			|| !position["y"].is<double>()) {
			return false;
		}

		std::string layoutTypeStr = root["layout_type"].get<std::string>();
		if (layoutTypeStr == "vertival") {
			this->layoutType = LayoutType::VERTICAL;
		}
		else {
			this->layoutType = LayoutType::HORIZONTAL;
		}

		this->size = sf::Vector2f(
			size["width"].get<double>(),
			size["height"].get<double>());

		this->position = sf::Vector2f(
			position["x"].get<double>(),
			position["y"].get<double>());

		this->vsyncEnabled = root["vsync_enabled"].get<bool>();
		return true;
	};

	picojson::value WindowConfig::GetJsonValue() {
		picojson::object root;
		std::string layoutTypeStr = "";
		if (this->layoutType == LayoutType::VERTICAL) {
			layoutTypeStr = "vertical";
		}
		else {
			layoutTypeStr = "horizontal";
		}
		root.insert(std::make_pair("layout_type", picojson::value(layoutTypeStr)));
		root.insert(std::make_pair("vsync_enabled", picojson::value(this->vsyncEnabled)));
		
		picojson::object sizeObj;
		sizeObj.insert(
			std::make_pair("width", picojson::value(static_cast<double>(this->size.x))));
		sizeObj.insert(
			std::make_pair("height", picojson::value(static_cast<double>(this->size.y))));
		root.insert(std::make_pair("size", picojson::value(sizeObj)));

		picojson::object positionObj;
		positionObj.insert(
			std::make_pair("x", picojson::value(static_cast<double>(this->position.x))));
		positionObj.insert(
			std::make_pair("y", picojson::value(static_cast<double>(this->position.y))));
		root.insert(std::make_pair("position", picojson::value(positionObj)));
		return picojson::value(root);
	};
}};