////////////////////////////////////////
//(c) 2016  white   ResourceMapping
////////////////////////////////////////

//#include "ResourceMapping.hpp"
#include "JsonFileStorage.hpp"
/*
bool jubeon::storages::ResourceMapping::load(const std::string fpath)
{
	//Load file
	storages::JsonFileStorage jfstorage(fpath);

	std::shared_ptr<ResourceMapping> inst = jfstorage.getModel<ResourceMapping>();
	
	

	return false;
}

bool jubeon::storages::ResourceMapping::Init(picojson::value val)
{
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

	return false;
}
*/