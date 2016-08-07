#include "PanelPosition.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"

jubeon::game::PanelPosition::PanelPosition()
{
	for (auto p : this->panel_rect) p = sf::IntRect(0, 0, 100, 100);
}

const sf::IntRect & jubeon::game::PanelPosition::get(unsigned char panel_no) const
{
	return this->panel_rect.at(panel_no);
}

bool jubeon::game::PanelPosition::loadJson(const std::string json_file)
{
	storages::JsonFileStorage jsto(json_file);
	std::shared_ptr<PanelPosition> ret = jsto.getModel<PanelPosition>();

	if (ret) {
		this->panel_rect = ret->panel_rect;
		return true;
	}

	return false;
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

bool jubeon::game::PanelPosition::Init(picojson::value val)
{

	try {
		auto root = val.get<picojson::object>();
		auto keyconfig = root["panel_position"].get<picojson::array>();
		for (int i = 0; i < keyconfig.size(); i++) {
			auto param = keyconfig.at(i).get<picojson::array>();
			this->panel_rect[i].left = static_cast<int>(param.at(0).get<double>());
			this->panel_rect[i].top = static_cast<int>(param.at(1).get<double>());
			this->panel_rect[i].width = static_cast<int>(param.at(2).get<double>());
			this->panel_rect[i].height = static_cast<int>(param.at(3).get<double>());
		}
	}
	catch (std::exception e) {
		systems::Logger::error("パネル位置のjsonファイル読込中に例外が発生しました。" + std::string(e.what()));
		return false;
	}

	return true;
}

picojson::value jubeon::game::PanelPosition::GetJsonValue()
{
	//TO DO : 保存関数を実装
	return picojson::value();
}
