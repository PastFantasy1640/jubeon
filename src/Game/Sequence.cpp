#include "Sequence.hpp"

jubeon::game::Sequence::Sequence(const SPNotes notes)
	: notes(notes)
{
}

jubeon::game::SPNotes jubeon::game::Sequence::getNotes(void)
{
	return this->notes;
}

jubeon::game::Note jubeon::game::Sequence::operator[] (const size_t idx) {
	return this->notes->at[idx];
}

