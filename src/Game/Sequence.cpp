#include "Sequence.hpp"

jubeat_online::game::Sequence::Sequence()
{
}

jubeat_online::game::Sequence::Sequence(const Sequence & cp)
{
}


jubeat_online::game::Sequence::Sequence(const std::vector<Note> notes)
{
	this->notes.reset(new std::vector<Note>(notes));
}

jubeat_online::game::SPNotes jubeat_online::game::Sequence::getNotes(void)
{
	return this->notes;
}
