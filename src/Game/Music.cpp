#include "Music.hpp"

unsigned int jubeon::game::Music::getPlayingCurrentTime(void) const
{	
	//���Ԃ��擾
	return this->soundplayer.getPlayingOffset().asMilliseconds();
}

void jubeon::game::Music::startToPlay(void)
{
	//�X���b�h�Z�[�t�΍�
	//std::lock_guard<std::mutex> lock(this->mtx);

	//�Đ�
	this->soundplayer.play();
}

void jubeon::game::Music::startToPlayForSM(void)
{
}
