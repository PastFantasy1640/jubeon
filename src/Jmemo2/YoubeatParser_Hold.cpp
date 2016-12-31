#include "YoubeatParser.hpp"

jubeon::parser::YoubeatParser::Hold::Hold(const jPanel to, const jPanel from, const char endc)
	: to(to), from(from), end_charactor(endc)
{
}

jubeon::parser::YoubeatParser::Hold::Hold(const Hold & copy)
	: to(copy.to), from(copy.from), end_charactor(copy.end_charactor)
{
}
