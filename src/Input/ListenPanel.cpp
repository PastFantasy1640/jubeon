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
    : is_queue_(false),
    is_thread_exit_(false),
    offset(0)
{
    for(auto i : this->push_flags) i = false;
    this->quebuf.addInputStream(&this->input);
}

jubeon::input::ListenPanel::~ListenPanel(){
}

//////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////
void jubeon::input::ListenPanel::startThread(void){

    //restart clock
	panel_clock_.restart();

    //flags
    this->is_thread_exit_ = false;

	//start thread
	this->check_th_.reset(new std::thread(&ListenPanel::ThreadFunc, this));
}

void jubeon::input::ListenPanel::Close(void){
	is_thread_exit_ = true;
    this->check_th_->join();
}


void jubeon::input::ListenPanel::SetQue(const int n) {

    // is queue stopping
	if (!this->is_queue_) return;

	this->push_flags[n] ^= true;
	sf::Time t = panel_clock_.getElapsedTime();
	PanelInput tmp;
	tmp.ms = t.asMilliseconds() - offset;
	tmp.panel_no = n;
	tmp.t = (this->push_flags[n] ? Type::PUSH : Type::RELEASE);

	this->input << tmp;
	this->quebuf.flush();
}

void jubeon::input::ListenPanel::ThreadFunc(void) {
	while (!this->is_thread_exit_) {
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
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

void jubeon::input::ListenPanel::setListenFlag(const bool flag) {
	this->is_queue_ = flag;
}

bool jubeon::input::ListenPanel::isListening() const{
	return this->is_queue_;
}

void jubeon::input::ListenPanel::restartTimer(const int offset)
{
	this->offset = panel_clock_.getElapsedTime().asMilliseconds() - offset;
}


