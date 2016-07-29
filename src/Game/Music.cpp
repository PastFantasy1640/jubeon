#include "Music.hpp"

unsigned int jubeat_online::game::Music::getPlayingCurrentTime(void) const
{	
	//時間を取得
	return this->soundplayer.getPlayingOffset().asMilliseconds();
}

void jubeat_online::game::Music::startToPlay(void)
{
	//スレッドセーフ対策
	//std::lock_guard<std::mutex> lock(this->mtx);

	//再生
	this->soundplayer.play();
}

void jubeat_online::game::Music::startToPlayForSM(void)
{
}
