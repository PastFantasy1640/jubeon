#include "Sequence.hpp"
#include "PlayRecord.hpp"


jubeon::game::Note::Note(const int just_time, const int panel_idx)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(0),
	holdMarkerIndex(-1)
{
}

jubeon::game::Note::Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx)
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

int jubeon::game::Note::getHoldMarkerIndex(void) const
{
	return this->holdMarkerIndex;
}
