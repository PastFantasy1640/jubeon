////////////////////////////////////////////////////
// (c) 2015  white
//author white
//2015/10/23 made
////////////////////////////////////////////////////

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
    : offset(0),
    input(new strbuf::InputStream<jubeon::input::EventContainer>)
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

		*(this->input) << EventContainer(e, this->clock.getElapsedTime() + sf::milliseconds(this->offset));
        this->flush();
        
        systems::Logger::information("Queued.");
	}

	systems::Logger::information("Closed event queuing function.");
}

void jubeon::input::Event::restartTimer(const int offset)
{
	this->offset = this->clock.getElapsedTime().asMilliseconds() - offset;
}


