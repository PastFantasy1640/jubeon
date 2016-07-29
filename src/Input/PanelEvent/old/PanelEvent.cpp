
#include "PanelEvent.hpp"

jubeat_online::PanelEvent::PanelEvent() {}	//ŒÄ‚Î‚ê‚é‚Í‚¸‚ª‚È‚¢

jubeat_online::PanelEvent::~PanelEvent() {}

jubeat_online::PanelEvent::PanelEvent(const jubeat_online::PanelEvent & obj) {
	this->player_id_ = obj.player_id_;
	this->type_ = obj.type_;
	this->ms_ = obj.ms_;
	this->panel_index_ = obj.panel_index_;
}

jubeat_online::PanelEvent::PanelEvent(const short player_id, const PanelEventType type, const unsigned int ms,	const unsigned int p_index) {
	
	//‰Šú‰»
	this->player_id_ = player_id;
	this->type_ = type;
	this->ms_ = ms;
	this->panel_index_ = p_index;
}

unsigned int jubeat_online::PanelEvent::getPanelIndex() const {
	return this->panel_index_;
}

short jubeat_online::PanelEvent::getPlayerID() const {
	return this->player_id_;
}

jubeat_online::PanelEvent::PanelEventType jubeat_online::PanelEvent::getEventType() const{
	return this->type_;
}

unsigned int jubeat_online::PanelEvent::getEventTime(void) const
{
	return this->ms_;
}

std::string jubeat_online::PanelEvent::ToString(void) const
{
	std::string ret = "[";
	//‚Ü‚¸type
	switch (this->getEventType()) {
	case PUSH:		ret += "PUSH   "; break;
	case RELEASE:	ret += "RELEASE"; break;
	default:		ret += "NONE   "; break;
	}

	ret += "]ID:(";

	ret += std::to_string(this->getPlayerID()) + ")index->";

	ret += std::to_string(this->getPanelIndex()) + (this->getPanelIndex() < 10 ? "  " : " ") + "time->";

	ret += std::to_string(this->getEventTime());
	
	return ret;
}
