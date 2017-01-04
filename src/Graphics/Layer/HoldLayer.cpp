#include "HoldLayer.hpp"
#include <string>
#include <sstream>
#include <iomanip>

#include "Systems/Logger.hpp"

jubeon::game::layers::HoldLayer::HoldLayer(Player * const player)
	: player(player)
{
}

void jubeon::game::layers::HoldLayer::Init()
{
	std::ostringstream sout;

	//holdarrow
	systems::Logger::information("[MarkerLayer]Start to load the hold resources.");
	for (int file_no = 0; file_no < 20; file_no++) {
        sout << "media/marker/hold/holdarrow/holdarrow_" << std::setfill('0') << std::setw(5) << file_no;
		this->arrow_tex.emplace_back(sf::Texture());
		
		if (!this->arrow_tex.at(file_no).loadFromFile(sout.str() + ".png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : " + sout.str() + ".png");
		}
		sout.clear();
	}

	for (int file_no = 0; file_no < 20; file_no++) {
        sout << "media/marker/hold/holdpanel/holdpanel_" << std::setfill('0') << std::setw(5) << file_no;
		this->arrow_tex.emplace_back(sf::Texture());
		
		if (!this->arrow_tex.at(file_no).loadFromFile(sout.str() + ".png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : " + sout.str() + ".png");
		}
		sout.clear();
	}

	if (!this->line_tex.loadFromFile("media/marker/hold/holdline.png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : media/marker/hold/holdline.png");
	}
	
	if (!this->line_tex.loadFromFile("media/marker/hold/holdto.png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : media/marker/hold/holdto.png");
	}

}

void jubeon::game::layers::HoldLayer::Draw()
{
}

void jubeon::game::layers::HoldLayer::Exit()
{
}
