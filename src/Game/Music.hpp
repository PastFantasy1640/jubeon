#pragma once

#ifndef JUBEAT_ONLINE_MUSIC_HPP
#define JUBEAT_ONLINE_MUSIC_HPP

#include <mutex>
#include <SFML/Audio.hpp>

namespace jubeat_online {
	namespace game {
		class Music {
		public:
			
			//�Đ����̎��Ԃ��擾����֐��i�X���b�h�Z�[�t�j
			unsigned int getPlayingCurrentTime(void) const;

			//�Đ����J�n����
			void startToPlay(void);

			//�Z���N�g�~���[�W�b�N�p�ɍĐ�����B�w�肳�ꂽ�Ƃ����FI�AFO����
			void startToPlayForSM(void);

			//****TO DO : �������Apublic�̈�
			//�ȃf�[�^
			sf::SoundBuffer soundbuffer;
			//�v���C���[
			sf::Sound soundplayer;
		private:

			//�X���b�h�Z�[�t�΍�
		//	std::mutex mtx;





		};
	}
}

#endif