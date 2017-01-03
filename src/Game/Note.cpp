#include "Sequence.hpp"
#include "PlayRecord.hpp"

//hold is duration > 0

jubeon::game::Note::Note(const jMillisec just_time, const jPanel panel_idx, const bool is_hold_end)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(0),
	holdMarkerIndex((is_hold_end ? 0xff : 0))
{
}

jubeon::game::Note::Note(const jMillisec just_time, const jPanel panel_idx, const int duration, const int holdmarker_panel_idx)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(duration),
	holdMarkerIndex(holdmarker_panel_idx)
{
}


int jubeon::game::Note::getJustTime(void) const
{
	return this->justTime;
}

int jubeon::game::Note::getPanelIndex(void) const
{
	return this->panelIndex;
}

int jubeon::game::Note::getHoldDuration(void) const
{
	return this->duration;
}

int jubeon::game::Note::getHoldEndTime(void) const
{
	return this->getJustTime() + this->getHoldDuration();
}

int jubeon::game::Note::getHoldMarkerIndex(void) const
{
	return this->holdMarkerIndex;
}

bool jubeon::game::Note::isHold(void) const
{
	return this->getHoldDuration() != 0;
}

bool jubeon::game::Note::isHoldEnd(void) const
{
	return (this->getHoldMarkerIndex() == 0xff);
}
