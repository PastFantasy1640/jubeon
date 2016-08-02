#include "Music.hpp"

unsigned int jubeon::game::Music::getPlayingCurrentTime(void) const
{	
	//時間を取得
	return this->soundplayer.getPlayingOffset().asMilliseconds();
}

void jubeon::game::Music::startToPlay(void)
{
	//スレッドセーフ対策
	//std::lock_guard<std::mutex> lock(this->mtx);

	//再生
	this->soundplayer.play();
}

void jubeon::game::Music::startToPlayForSM(void)
{
}
