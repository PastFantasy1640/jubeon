#include "Sequence.hpp"
#include "PlayRecord.hpp"


jubeat_online::game::Note::Note(const int just_time, const int panel_idx)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(0),
	holdMarkerIndex(-1)
{
}

jubeat_online::game::Note::Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(duration),
	holdMarkerIndex(holdmarker_panel_idx)
{
}

jubeat_online::game::Note::Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx, const std::shared_ptr<PanelInput> judge)
	: justTime(just_time),
	panelIndex(panel_idx),
	duration(duration),
	holdMarkerIndex(holdmarker_panel_idx),
	judged(judge)
{
}

int jubeat_online::game::Note::getJustTime(void) const
{
	return this->justTime;
}

int jubeat_online::game::Note::getPanelIndex(void) const
{
	return this->panelIndex;
}

int jubeat_online::game::Note::getHoldDuration(void) const
{
	return this->duration;
}

int jubeat_online::game::Note::getHoldMarkerIndex(void) const
{
	return this->holdMarkerIndex;
}

void jubeat_online::game::Note::getJudge(int * ms_diff, Judge * judge) const
{
	*ms_diff = this->judged->ms;
	*judge = this->judged->j;	
}
