#include "Music.hpp"

unsigned int jubeat_online::game::Music::getPlayingCurrentTime(void) const
{	
	//���Ԃ��擾
	return this->soundplayer.getPlayingOffset().asMilliseconds();
}

void jubeat_online::game::Music::startToPlay(void)
{
	//�X���b�h�Z�[�t�΍�
	//std::lock_guard<std::mutex> lock(this->mtx);

	//�Đ�
	this->soundplayer.play();
}

void jubeat_online::game::Music::startToPlayForSM(void)
{
}
