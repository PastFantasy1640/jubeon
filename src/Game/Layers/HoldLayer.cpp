#include "HoldLayer.hpp"
#include <string>
#include <sstream>
#include <iomanip>

#include "Systems/Logger.hpp"

jubeon::game::layers::HoldLayer::HoldLayer(Player * const player, const PanelPosition & panel_position, const Music * music)
	: player(player), ppos(panel_position), music(music)
{
}

void jubeon::game::layers::HoldLayer::Init()
{

	//holdarrow
	systems::Logger::information("[MarkerLayer]Start to load the hold resources.");
	for (int file_no = 0; file_no < 20; file_no++) {
		std::ostringstream sout;
        sout << "media/marker/hold/holdarrow/holdarrow_" << std::setfill('0') << std::setw(5) << file_no;
		this->arrow_tex.emplace_back(sf::Texture());
		
		if (!this->arrow_tex.at(file_no).loadFromFile(sout.str() + ".png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : " + sout.str() + ".png");
		}
	}

	for (int file_no = 0; file_no < 20; file_no++) {
		std::ostringstream sout;
        sout << "media/marker/hold/holdpanel/holdpanel_" << std::setfill('0') << std::setw(5) << file_no;
		this->panel_tex.emplace_back(sf::Texture());
		
		if (!this->panel_tex.at(file_no).loadFromFile(sout.str() + ".png")) {
			systems::Logger::error("[MarkerLayer]There is no resource. FILE : " + sout.str() + ".png");
		}
	}

	if (!this->line_tex.loadFromFile("media/marker/hold/holdline.png")) {
		systems::Logger::error("[MarkerLayer]There is no resource. FILE : media/marker/hold/holdline.png");
	}
	
	if (!this->holdto_tex.loadFromFile("media/marker/hold/holdto.png")) {
		systems::Logger::error("[MarkerLayer]There is no resource. FILE : media/marker/hold/holdto.png");
	}

}

void jubeon::game::layers::HoldLayer::Draw()
{
	this->clearBuffer();


	this->_holdtoDraw();

}

void jubeon::game::layers::HoldLayer::Exit()
{
}


void jubeon::game::layers::HoldLayer::_holdtoDraw()
{
//	const Notes * hold_list = this->player->getPlayRecord()->getHoldingList();
	Notes::const_iterator begin = this->player->getSequence()->search(this->player->getCurrentTime(this->music) - this->player->getMarker()->getLengthAfterMax());
	Notes::const_iterator end = this->player->getSequence()->search(this->player->getCurrentTime(this->music) + this->player->getMarker()->getLengthBefore());

	std::array<bool, 16> is_draw{ false };

	//Hold Marker
	sf::Sprite markersp(this->holdto_tex);
	
	//‚±‚±‚Éhold_list‚É‚æ‚é•`ŽÊ‚à’Ç‰Á

	for (auto ite = begin; ite != end; ite++) {
		if (ite->second == nullptr && ite->first.isHold() && !ite->first.isHoldEnd() && !is_draw.at(ite->first.getPanelIndex())) {
			const sf::IntRect & rect = this->ppos.get(ite->first.getPanelIndex());
			
			is_draw.at(ite->first.getPanelIndex()) = true;

			markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			markersp.setScale(static_cast<double>(rect.width) / this->holdto_tex.getSize().x, static_cast<double>(rect.height) / this->holdto_tex.getSize().y);
			this->draw(markersp);
		}
	}
}
