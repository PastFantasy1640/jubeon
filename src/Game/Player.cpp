#include "Player.hpp"
#include "Models/Configures.hpp"

jubeon::game::Player::Player()
{
	this->pinput_sb.addInputStream(this->pinput_input);
}

jubeon::game::Player::~Player()
{
}

void jubeon::game::Player::setInputFromEvent(input::Event & instance)
{
	instance.addOutputStream(this->event_output);
}

const jubeon::game::PlayRecord * jubeon::game::Player::getPlayRecord(void) const
{
	return &this->record;
}

void jubeon::game::Player::updateInput(Sequence & seq)
{
	//Select Input data
	while (this->event_output->getQueSize()) {
		input::EventContainer p = this->event_output->unque();

		if (p.e.type == sf::Event::KeyPressed || p.e.type == sf::Event::KeyReleased) {
			for (size_t pidx = 0; pidx <= models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
				if (models::Configures::getInstance()->panel_config->getHidID(pidx) == -1) {
					if (models::Configures::getInstance()->panel_config->getKeyCode(pidx) == p.e.key.code) {
						this->pinput_input->que(input::PanelInput(pidx, (p.e.type == sf::Event::KeyPressed ? PUSH : RELEASE), p.time.asMicroseconds()));
						this->pinput_sb.flush();
						break;
					}
				}
			}
		}
		else if (p.e.type == sf::Event::JoystickButtonPressed || p.e.type == sf::Event::JoystickButtonReleased) {
			for (size_t pidx = 0; pidx <= models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
				if (models::Configures::getInstance()->panel_config->getHidID(pidx) == p.e.joystickButton.joystickId) {
					if (models::Configures::getInstance()->panel_config->getJoystickCode(pidx) == p.e.joystickButton.button) {
						this->pinput_input->que(input::PanelInput(pidx, (p.e.type == sf::Event::JoystickButtonPressed ? PUSH : RELEASE), p.time.asMicroseconds()));
						this->pinput_sb.flush();
						break;
					}
				}
			}
		}
	}
	this->pinput_sb.flush();

	while (this->pinput_output->getQueSize()) {
		input::PanelInput p = this->pinput_output->unque();

		this->record.judge(seq, p);
	}
}
