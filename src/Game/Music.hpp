#pragma once

#ifndef jubeon_MUSIC_HPP
#define jubeon_MUSIC_HPP

#include <array>
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		class Music {
		public:
			
			//�R���X�g���N�^
			Music(




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

			//�����o�[�ϐ�
			int									music_id;					//�y��ID
			const std::string					metafile_path;				//���^�t�@�C���p�X
			std::array<std::string, 3>			notes_filepath;				//�m�[�c�̕��ʃt�@�C���p�X
			std::array<int, 3>					high_score;					//�n�C�X�R�A
			std::array<std::string, 3>	high_score_pr_filepath;		//�v���C�L�^�t�@�C���i�ō��j�̃t�@�C���p�X
				
			std::array<std::string, 3>	latest_score_pr_filepath;	//�v���C�L�^�t�@�C���i���߁j�̃t�@�C���p�X

			const std::string					name;						//�Ȗ�
			const std::string					artist;						//�A�[�e�B�X�g��
			const std::string					sound_filepath;				//�y�ȃt�@�C���p�X

			std::unique_ptr<sf::SoundBuffer>	up_sound_buffer;			//�o�b�t�@
			const sf::Sound						sound;						//�v���C���[
			const sf::Image						thumbnail;					//�T���l
			
			//TO DO : MusicBar�͖���`
			//std::array<MusicBar, 3>	musicbar_challenge;	//�~���[�W�b�N�o�[�`�������W
			

			//��̂��Ƃ��f�t�H���g�R���X�g���N�^�͋֎~�B
			Music(void);
		};
	}
}

#endif