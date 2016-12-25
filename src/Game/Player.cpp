#include "Player.hpp"
#include "Models/Configures.hpp"
#include "Marker.hpp"

jubeon::game::Player::Player()
	: marker(new Marker())
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
	//Select Input data
	/*while (this->event_output->getQueSize()) {
		input::EventContainer p = this->event_output->unque();

		if (p.e.type == sf::Event::KeyPressed || p.e.type == sf::Event::KeyReleased) {
			for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
				if (models::Configures::getInstance()->panel_config->getHidID(pidx) == -1) {
					if (models::Configures::getInstance()->panel_config->getKeyCode(pidx) == p.e.key.code) {
						this->pinput_input->que(input::PanelInput(pidx, (p.e.type == sf::Event::KeyPressed ? PUSH : RELEASE), p.time.asMilliseconds() - this->offset));
						this->pinput_sb.flush();
						break;
					}
				}
			}
		}
		else if (p.e.type == sf::Event::JoystickButtonPressed || p.e.type == sf::Event::JoystickButtonReleased) {
			for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
				if (models::Configures::getInstance()->panel_config->getHidID(pidx) == p.e.joystickButton.joystickId) {
					if (models::Configures::getInstance()->panel_config->getJoystickCode(pidx) == p.e.joystickButton.button) {
						this->pinput_input->que(input::PanelInput(pidx, (p.e.type == sf::Event::JoystickButtonPressed ? PUSH : RELEASE), p.time.asMilliseconds() - this->offset));
						this->pinput_sb.flush();
						break;
					}
				}
			}
		}
	}
	this->pinput_sb.flush();*/

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



/*
void jubeon::game::Player::setInputFromEvent(input::Event * instance, const game::Music * music)
{
	instance->addOutputStream(this->event_output);
	this->playing_music.reset(music);
}

const jubeon::game::PlayRecord * jubeon::game::Player::getPlayRecord(void) const
{
	return &this->record;
}

void jubeon::game::Player::updateInput(Sequence * seq)
{

}


*/