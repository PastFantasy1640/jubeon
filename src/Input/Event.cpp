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
#include "ListenPanel.hpp"

//configuration
#include "Models/PanelConfig.hpp"

//for logging
#include "Systems/Logger.hpp"

/////////////////////////////////////////////////////
// Singleton Instance
/////////////////////////////////////////////////////
std::unique_ptr<jubeon::input::ListenPanel> jubeon::input::ListenPanel::instance(new jubeon::input::ListenPanel);

jubeon::input::ListenPanel * jubeon::input::ListenPanel::getInstance(){
    return ListenPanel::instance.get();
}


/////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////
jubeon::input::ListenPanel::ListenPanel()
    : offset(0),
    input(new strbuf::InputStream<sf::Event>)
{
    for(auto i : this->push_flags) i = false;
}

jubeon::input::ListenPanel::~ListenPanel(){
}

//////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////
void jubeon::input::ListenPanel::process(jubeon::graphics::LayerManager * main_window){

    //restart clock
	panel_clock_.restart();

    main_window->getEventBuffer()->addInputStream(this->input);

	//start thread
	this->ThreadFunc(main_window);
}

/*
void jubeon::input::ListenPanel::SetQue(const int n) {

    // is queue stopping
	if (!this->is_queue_) return;

	this->push_flags[n] ^= true;
	sf::Time t = panel_clock_.getElapsedTime();
	PanelInput tmp;
	tmp.ms = t.asMilliseconds() - offset;
	tmp.panel_no = n;
	tmp.t = (this->push_flags[n] ? Type::PUSH : Type::RELEASE);

	*(this->input) << tmp;
	this->quebuf.flush();
}
*/
void jubeon::input::ListenPanel::ThreadFunc(jubeon::graphics::LayerManager * main_window) {

    bool is_exit = false;

	while (!is_exit && main_window->isOpen()) {
	    sf::Event e;
	    if(!main_window->waitEvent(e)) break;

        //Queue
        *(this->input) << e;
        main_window->getEventBuffer()->flush();
        
        systems::Logger::information("Queued.");
        
        	/*
		for (int n = 0; n < 16; n++) {
			if (jubeon::models::PanelConfig::getInstance()->getHidID(n) != -1) {
				if (sf::Joystick::isButtonPressed(jubeon::models::PanelConfig::getInstance()->getHidID(n), jubeon::models::PanelConfig::getInstance()->getJoystickCode(n)) ^ this->push_flags[n]) SetQue(n);
			}
			else {
				//-1‚ªkeyboard
//				if (sf::Keyboard::isKeyPressed(jubeon::models::PanelConfig::getInstance()->getKeyCode(n)) ^ this->push_flags[n]) SetQue(n);
                //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ;
			}
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));*/
	}
}

void jubeon::input::ListenPanel::restartTimer(const int offset)
{
	this->offset = panel_clock_.getElapsedTime().asMilliseconds() - offset;
}


