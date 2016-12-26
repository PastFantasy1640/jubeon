#include "Player.hpp"
#include "Models/Configures.hpp"
#include "Marker.hpp"

jubeon::game::Player::Player()
	: marker(new Marker())
{
}

jubeon::game::Player::Player(const std::string player_name)
	: name(player_name)
{
}

jubeon::game::Player::~Player()
{
}

void jubeon::game::Player::initForPlay(strbuf::StreamBuffer<input::PanelInput>* panel_strbuf, const int playing_offset)
{
	panel_que.reset(new strbuf::OutputStream<input::PanelInput>());
	panel_strbuf->addOutputStream(panel_que);
	this->setPlayerOffset(playing_offset);
	this->record.reset(new PlayRecord());
}

void jubeon::game::Player::setMarker(const std::shared_ptr<Marker>& new_marker)
{
	marker = new_marker;
}

void jubeon::game::Player::setMarker(const Marker & new_marker)
{
//	marker.reset(new Marker(new_marker));
}

const jubeon::game::Marker * jubeon::game::Player::getMarker(void) const
{
	return this->marker.get();
}

jubeon::game::PlayRecord * jubeon::game::Player::getPlayRecord(void)
{
	return this->record.get();
}

void jubeon::game::Player::updateInput(Sequence * seq)
{
	

	while (this->panel_que->getQueSize()) {
		input::PanelInput p = this->panel_que->unque();

		this->record->judge(*seq, p);
	}
}

void jubeon::game::Player::setPlayerOffset(const int offset)
{
	this->offset = offset;
}

int jubeon::game::Player::getPlayerOffset(void) const
{
	return this->offset;
}

int jubeon::game::Player::getCurrentTime(const Music * music) const
{
	return music->getPlayingCurrentTime() + this->offset;
}


