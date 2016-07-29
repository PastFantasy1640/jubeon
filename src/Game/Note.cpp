#include "Note.hpp"

jubeat_online::game::Note::Note(const unsigned char panel_no, const unsigned int ms)
	: panel_no(panel_no),
	ms(ms)
{
}

jubeat_online::game::HoldNote::HoldNote(const unsigned char panel_no, const unsigned int ms, unsigned char appear_panel_no, unsigned int holdend_ms)
	: appear_panel_no(appear_panel_no),
	holdend_ms(holdend_ms),
	Note(panel_no, ms)
{
}
