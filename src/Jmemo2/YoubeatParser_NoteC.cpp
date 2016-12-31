#include "YoubeatParser.hpp"

jubeon::parser::YoubeatParser::Note_C::Note_C(const unsigned int haku, const unsigned int m, const unsigned int v, const jubeon::jPanel p_no)
	: haku(haku), m(m), v(v),p_no(p_no)
{
}

jubeon::game::Note jubeon::parser::YoubeatParser::Note_C::convertToNote(const BpmTable bpm_table, const jMillisec offset) const
{
	BpmTable::const_iterator p = bpm_table.begin();

	for (; p != bpm_table.end(); p++) {
		if (p->haku > this->haku) break;
	}

	double paramA = 0.0f;
	double paramB = 0.0f;
	double ms = 0.0f;

	// != p ‚Ü‚Å‚Æ‚µ‚ÄŒvŽZ‚·‚ê‚Î‚¢‚¢
	for (BpmTable::const_iterator cur = bpm_table.begin(); cur != p; cur++) {
		ms = paramA * cur->haku + paramB;
		
		paramA = 60000.0f / cur->bpm;
		paramB = ms - paramA * cur->haku;
	}

	//ms = paramA * (haku + m / v) + paramB
	return jubeon::game::Note(paramA * (static_cast<double>(this->haku) + static_cast<double>(this->m) / static_cast<double>(this->v)) + paramB + offset, this->p_no);

}