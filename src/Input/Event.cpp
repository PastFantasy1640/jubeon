////////////////////////////////////////////////////
// (c) 2015  white
//author white
//2015/10/23 made
////////////////////////////////////////////////////

#include "Event.hpp"

#include "Systems/Logger.hpp"
/*
strbuf::StreamBuffer<jubeon::input::PanelInput>* jubeon::game::scenes::EventBase::getPanelStreamBuf(void)
{
	return &this->pinput_sb;
}

jubeon::game::scenes::EventBase::EventBase()
	: pinput_que(new strbuf::InputStream<input::PanelInput>())
{
	this->pinput_sb.addInputStream(this->pinput_que);
}

template<typename T>
jubeon::input::EventBase<T>::~EventBase()
{
}

void jubeon::game::scenes::EventBase::EventToPanel(sf::Event e)
{
	//Select Input data

	if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
		for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
			if (models::Configures::getInstance()->panel_config->getHidID(pidx) == -1) {
				if (models::Configures::getInstance()->panel_config->getKeyCode(pidx) == e.key.code) {
					//getPlayingCurrentTime is const function so this is thread safe.
					this->pinput_que->que(input::PanelInput(pidx, (e.type == sf::Event::KeyPressed ? PUSH : RELEASE), music->getPlayingCurrentTime()));
					this->pinput_sb.flush();
					break;
				}
			}
		}
	}
	else if (e.type == sf::Event::JoystickButtonPressed || e.type == sf::Event::JoystickButtonReleased) {
		for (size_t pidx = 0; pidx < models::Configures::getInstance()->panel_config->getPanelNum(); pidx++) {
			if (models::Configures::getInstance()->panel_config->getHidID(pidx) == e.joystickButton.joystickId) {
				if (models::Configures::getInstance()->panel_config->getJoystickCode(pidx) == e.joystickButton.button) {
					this->pinput_que->que(input::PanelInput(pidx, (e.type == sf::Event::JoystickButtonPressed ? PUSH : RELEASE), music->getPlayingCurrentTime()));
					this->pinput_sb.flush();
					break;
				}
			}
		}
	}
	this->pinput_sb.flush();
}

/*
std::vector<jubeon::input::Event *> jubeon::input::Event::events;


jubeon::input::Event::Event(sf::Window * layermanager)
	: window(layermanager)
{
	this->events.push_back(this);
}

jubeon::input::Event::~Event()
{
	for (auto p = this->events.begin(); p != this->events.end(); p++) {
		if (*p == this) {
			this->events.erase(p);
			break;
		}
	}
}

void jubeon::input::Event::setCallback(Callback function)
{
	{ //Mutable Area
		std::lock_guard<std::mutex> lock(this->mtx);
		this->cb = function;
	}
}

void jubeon::input::Event::run(void)
{
	bool is_exit = false;

	while (!is_exit && this->window->isOpen()) {
		sf::Event e;
		if (!this->window->waitEvent(e)) break;

		if (e.type == sf::Event::KeyPressed && e.key.alt == true && e.key.code == sf::Keyboard::F4) break;

		if(this->cb) this->cb(e);
	}

	systems::Logger::information("Closed event queuing function.");
}

bool jubeon::input::Event::getInstance(const sf::Window * layermanager, jubeon::input::Event * dst)
{
	for (auto p : Event::events) {
		if (p->window == layermanager) {
			dst = p;
			return true;
		}
	}
	dst = nullptr;
	return false;
}


/*
//for string
#include <string>

//for debugging
#include <iostream>

//my implements
#include "Event.hpp"

//configuration
#include "Models/PanelConfig.hpp"

//for logging
#include "Systems/Logger.hpp"

/////////////////////////////////////////////////////
// Singleton Instance
/////////////////////////////////////////////////////
std::unordered_map<const jubeon::graphics::LayerManager *, std::unique_ptr<jubeon::input::Event>> jubeon::input::Event::instance;

jubeon::input::Event * jubeon::input::Event::getInstance(const jubeon::graphics::LayerManager * window){
	if (!Event::instance.count(window)) {
		Event::instance[window].reset(new Event);
	}
    return Event::instance[window].get();
}


/////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////
jubeon::input::Event::Event()
    : input(new strbuf::InputStream<jubeon::input::EventContainer>)
{
	//connect stream
	this->addInputStream(this->input);

	//restart clock
	this->clock.restart();
}

jubeon::input::Event::~Event(){
}

//////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////
void jubeon::input::Event::process(jubeon::graphics::LayerManager * main_window){
    bool is_exit = false;

	while (!is_exit && main_window->isOpen()) {
	    sf::Event e;
	    if(!main_window->waitEvent(e)) break;

		if (e.type == sf::Event::KeyPressed && e.key.alt == true && e.key.code == sf::Keyboard::F4) break;

        //Queue
        //check flag
		if (this->flags.count(e.type)) {
			if (!this->flags.at(e.type)) continue;	//Do not queue
		}

		*(this->input) << EventContainer(e, this->clock.getElapsedTime());
        this->flush();
        
	}

	systems::Logger::information("Closed event queuing function.");
}

const unsigned int jubeon::input::Event::getTimerCount() const
{
	return this->clock.getElapsedTime().asMilliseconds();
}
/*
void jubeon::input::Event::restartTimer(const int offset)
{
	this->offset = this->clock.getElapsedTime().asMilliseconds() - offset;
}

*/

