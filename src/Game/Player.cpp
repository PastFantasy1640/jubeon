#include "Player.hpp"
#include "Models/Configures.hpp"
#include "Systems/Logger.hpp"

jubeon::game::Player::Player()
	: name("Illegal Constructor"), marker(nullptr)
{
}

jubeon::game::Player::Player(const std::string player_name)
	: name(player_name), marker(nullptr)
{
}

jubeon::game::Player::~Player()
{
}

void jubeon::game::Player::initForPlay(strbuf::StreamBuffer<input::PanelInput>* panel_strbuf,
	std::vector<Note> & notes,
	const int playing_offset)
{
	//init and reset Sequence
	this->sequence.reset(new Sequence(notes));

	//reset PlayRecord
	this->record.reset(new PlayRecord());

	//connect PanelInput Streaming
	panel_que.reset(new strbuf::OutputStream<input::PanelInput>());
	panel_strbuf->addOutputStream(panel_que);

	//set playing offset
	this->offset = playing_offset;

	systems::Logger::information("Finished to initialize the player. PLAYER : [Name="
		+ this->name + ",offset=" + std::to_string(this->offset)
		+ ",Sequence.size=" + std::to_string(this->sequence->size())
		+ ",PlayRecord.size=" + std::to_string(this->record->size()) + "]");
}

void jubeon::game::Player::setMarker(Marker * new_marker)
{
	marker = new_marker;
}

const jubeon::game::Marker * jubeon::game::Player::getMarker(void) const
{
	if (this->marker == nullptr) systems::Logger::error("[ERROR:Player]Tried to get the marker data, but it is nullptr.");
	return this->marker;
}

jubeon::game::PlayRecord * jubeon::game::Player::getPlayRecord(void) const
{
	if (!this->record) systems::Logger::error("[ERROR:Player]Tried to get the playrecord data, but it is empty.");
	return this->record.get();
}

void jubeon::game::Player::updateInput(void)
{
	while (this->panel_que->getQueSize()) {
		input::PanelInput p = this->panel_que->unque();

		this->record->judge(*this->sequence.get(), p);
	}
}

int jubeon::game::Player::getCurrentTime(const Music * music) const
{
	return music->getPlayingCurrentTime() + this->offset;
}


