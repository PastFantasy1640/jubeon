#include "Sequence.hpp"

jubeat_online::game::Sequence::Sequence()
{
}

jubeat_online::game::Sequence::Sequence(const Sequence & cp)
{
}

jubeat_online::game::Sequence::Sequence(const std::string & filename)
	: filename(filename),
	is_loaded(false)
{
}

bool jubeat_online::game::Sequence::load()
{

	//ƒ[ƒh‚ğ‚·‚éŠÖ”

	//•ˆ–Ê‘®‚ª‚Ü‚¾ŒÅ‚Ü‚Á‚Ä‚¢‚È‚¢‚Ì‚Å

	for (int i = 0; i < 10; i++) {
		this->notes.push_back(Note(0, 4000 + i * 4000));
		this->notes.push_back(Note(0, 5000 + i * 4000));
		this->notes.push_back(Note(0, 6000 + i * 4000));
		this->notes.push_back(Note(0, 6500 + i * 4000));
		this->notes.push_back(Note(0, 7000 + i * 4000));
	}

	this->is_loaded = true;

	return true;
}

void jubeat_online::game::Sequence::deleteNotes()
{
	this->hold_notes.clear();
	this->notes.clear();
}

const std::vector<jubeat_online::game::Note>* jubeat_online::game::Sequence::getNotes() const
{
	return &(this->notes);
}

const std::vector<jubeat_online::game::HoldNote>* jubeat_online::game::Sequence::getHoldNote() const
{
	return &(this->hold_notes);
}

std::string jubeat_online::game::Sequence::getNotesFileName(void) const
{
	return this->filename;
}
