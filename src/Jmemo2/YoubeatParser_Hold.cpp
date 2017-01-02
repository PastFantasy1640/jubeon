#include "YoubeatParser.hpp"

jubeon::parser::YoubeatParser::Hold::Hold(const jPanel to, const jPanel from, const char endc)
	: to(to), from(from), end_charactor(endc), duration(0), start(nullptr), end(nullptr)
{
}

jubeon::parser::YoubeatParser::Hold::Hold(const Hold & copy)
	: to(copy.to), from(copy.from), end_charactor(copy.end_charactor), duration(copy.duration), start(nullptr), end(nullptr)
{
}

unsigned int jubeon::parser::YoubeatParser::Hold::getDuration(const BpmTable & bpm_table) const
{
	if (!this->emptyStart() & !this->emptyEnd()) {
		game::Note s = this->getStart()->convertToNote(bpm_table, 0);
		game::Note e = this->getEnd()->convertToNote(bpm_table, 0);
		return e.getJustTime() - s.getJustTime();
	}
	return 0;
}

const jubeon::parser::YoubeatParser::Note_C * jubeon::parser::YoubeatParser::Hold::getStart() const
{
	return this->start;
}

jubeon::parser::YoubeatParser::Note_C * jubeon::parser::YoubeatParser::Hold::getStart()
{
	return this->start;
}

bool jubeon::parser::YoubeatParser::Hold::emptyStart() const
{
	return (this->getStart() == nullptr);
}

const jubeon::parser::YoubeatParser::Note_C * jubeon::parser::YoubeatParser::Hold::getEnd() const
{
	return this->end;
}

bool jubeon::parser::YoubeatParser::Hold::emptyEnd() const
{
	return (this->getEnd() == nullptr);
}

void jubeon::parser::YoubeatParser::Hold::setStart(Note_C * const start)
{
	if (this->start == nullptr) this->start = start;
}

void jubeon::parser::YoubeatParser::Hold::setEnd(Note_C * const end)
{
	if (this->end == nullptr) this->end = end;
}

