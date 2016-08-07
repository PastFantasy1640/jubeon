
//author white
//2015/10/23 made

//class_panel_event.cpp
//panel_event.hpp�̓���

#include <thread>
#include <string>
#include <stdexcept>
#include <iostream>

#include "ListenPanel.hpp"

#include "Models/PanelConfig.hpp"

#include "Systems/Logger.hpp"



std::list<jubeon::input::PanelInput> jubeon::input::ListenPanel::que_;
std::mutex jubeon::input::ListenPanel::mtx_;
bool jubeon::input::ListenPanel::pushing_[16] = { false };
sf::Clock * jubeon::input::ListenPanel::panel_clock_ = NULL;
std::atomic<bool> jubeon::input::ListenPanel::is_thread_exit_ = false;
bool jubeon::input::ListenPanel::is_queue_ = true;
bool jubeon::input::ListenPanel::is_overflow_ = false;


int jubeon::input::ListenPanel::Listen(void) {
	//������
	que_.clear();

	//QUEUE_MAXSIZE�̑Ó���
	if (QUEUE_MAXSIZE < 1) {
		throw std::exception("Unexpected value : QUEUE_MAXSIZE must be more than 1.");
	}

	panel_clock_ = new sf::Clock;
	panel_clock_->restart();

	//�ʃX���b�h�����グ
	std::thread check_th(GetPanelThread);

	check_th.detach();

	return 0;
}

void jubeon::input::ListenPanel::Close(void){

	is_thread_exit_ = true;

}


void jubeon::input::ListenPanel::SetQue(const int n) {

	//������Ă���
	std::lock_guard<std::mutex> lock(mtx_);

	//�����L���[��~�Ȃ�X�L�b�v
	if (!is_queue_) return;

	pushing_[n] ^= true;
	sf::Time t = panel_clock_->getElapsedTime();
	PanelInput tmp;
	tmp.ms = t.asMilliseconds();
	tmp.panel_no = n;
	tmp.t = (pushing_[n] ? Type::PUSH : Type::RELEASE);


	//����������QUEUE_MAXSIZE�𒴂��Ă��Ȃ���
	if (que_.size() >= QUEUE_MAXSIZE) {
		//�擪��1���ׂ�
		//�܂����Ƃ͎v�����ǁAQUEUE_MAXSIZE��0�ȉ��Ƃ��͂��߂���
		ListenPanel::que_.pop_front();
	}
	ListenPanel::que_.push_back(tmp);
	
}

void jubeon::input::ListenPanel::GetPanelThread(void) {
	//���ꂪ�Ă΂��Ƃ��͕K�����������ς�ł���Ƃ�

	while (1) {
		for (int n = 0; n < 16; n++) {
			if (jubeon::models::PanelConfig::getInstance()->getHidID(n) != -1) {
				if (sf::Joystick::isButtonPressed(jubeon::models::PanelConfig::getInstance()->getHidID(n), jubeon::models::PanelConfig::getInstance()->getJoystickCode(n)) ^ pushing_[n]) SetQue(n);
			}
			else {
				//-1��keyboard
				if (sf::Keyboard::isKeyPressed(jubeon::models::PanelConfig::getInstance()->getKeyCode(n)) ^ pushing_[n]) SetQue(n);
			}
		}
		if (is_thread_exit_) return;
	}

}



std::vector<jubeon::input::PanelInput> jubeon::input::ListenPanel::getEvent(void){
	
	std::vector<PanelInput> retvec(ListenPanel::que_.begin(), ListenPanel::que_.end());
	ListenPanel::que_.clear();
	return retvec;
}

size_t jubeon::input::ListenPanel::getQueNum(void) {
	return que_.size();
}

void jubeon::input::ListenPanel::setListenFlag(const bool flag) {
	is_queue_ = flag;
}

bool jubeon::input::ListenPanel::IsListening() {
	return is_queue_;
}

bool jubeon::input::ListenPanel::IsOverflow(void) {
	return is_overflow_;
}

void jubeon::input::ListenPanel::ResetOverflowFlag(void) {
	is_overflow_ = false;
}