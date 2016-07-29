
//author white
//2015/10/23 made

//class_panel_event.cpp
//panel_event.hppの内部

#include <thread>
#include <string>
#include <stdexcept>
#include <iostream>

#include "ListenPanel.hpp"
#include "../../systems/INIFileReader/INIFileReader.hpp"
#include "../PanelConfig/PanelConfig.hpp"



std::list<jubeat_online::PanelEvent> jubeat_online::input::ListenPanel::que_;
std::mutex jubeat_online::input::ListenPanel::mtx_;
bool jubeat_online::input::ListenPanel::pushing_[16] = { false };
sf::Clock * jubeat_online::input::ListenPanel::panel_clock_ = NULL;
std::atomic<bool> jubeat_online::input::ListenPanel::is_thread_exit_ = false;
bool jubeat_online::input::ListenPanel::is_queue_ = true;
bool jubeat_online::input::ListenPanel::is_overflow_ = false;

int jubeat_online::input::ListenPanel::Listen(void) {
	//初期化
	que_.clear();

	//QUEUE_MAXSIZEの妥当性
	if (QUEUE_MAXSIZE < 1) {
		throw std::exception("Unexpected value : QUEUE_MAXSIZE must be more than 1.");
	}

	panel_clock_ = new sf::Clock;
	panel_clock_->restart();

	//別スレッド立ち上げ
	std::thread check_th(GetPanelThread);

	check_th.detach();

	return 0;
}

void jubeat_online::input::ListenPanel::Close(void){

	is_thread_exit_ = true;

}


void jubeat_online::input::ListenPanel::SetQue(const int n) {

	//押されていた
	std::lock_guard<std::mutex> lock(mtx_);

	//もしキュー停止ならスキップ
	if (!is_queue_) return;

	pushing_[n] ^= true;
	sf::Time t = panel_clock_->getElapsedTime();
	PanelEvent tmp(0, (pushing_[n] ? PanelEvent::PUSH : PanelEvent::RELEASE), t.asMilliseconds(), n);

	//総合件数がQUEUE_MAXSIZEを超えていないか
	if (que_.size() >= QUEUE_MAXSIZE) {
		//先頭を1件潰す
		//まさかとは思うけど、QUEUE_MAXSIZEが0以下とかはだめだよ
		ListenPanel::que_.pop_front();
	}
	ListenPanel::que_.push_back(tmp);
	
}

void jubeat_online::input::ListenPanel::GetPanelThread(void) {
	//これが呼ばれるときは必ず初期化が済んでいるとき

	while (1) {
		for (int n = 0; n < 16; n++) {
			if (jubeat_online::config::Panel::getHidID(n) != -1) {
				if (sf::Joystick::isButtonPressed(jubeat_online::config::Panel::getHidID(n), jubeat_online::config::Panel::getJoystickCode(n)) ^ pushing_[n]) SetQue(n);
			}
			else {
				//-1がkeyboard
				if (sf::Keyboard::isKeyPressed(jubeat_online::config::Panel::getKeyCode(n)) ^ pushing_[n]) SetQue(n);
			}
		}
		if (is_thread_exit_) return;
	}

}



std::vector<jubeat_online::PanelEvent> jubeat_online::input::ListenPanel::getEvent(void){
	
	std::vector<PanelEvent> retvec(ListenPanel::que_.begin(), ListenPanel::que_.end());
	ListenPanel::que_.clear();
	return retvec;
}

size_t jubeat_online::input::ListenPanel::getQueNum(void) {
	return que_.size();
}

void jubeat_online::input::ListenPanel::setListenFlag(const bool flag) {
	is_queue_ = flag;
}

bool jubeat_online::input::ListenPanel::IsListening() {
	return is_queue_;
}

bool jubeat_online::input::ListenPanel::IsOverflow(void) {
	return is_overflow_;
}

void jubeat_online::input::ListenPanel::ResetOverflowFlag(void) {
	is_overflow_ = false;
}