#pragma once

#ifndef JUBEON_GAME_MUSIC_HPP
#define JUBEON_GAME_MUSIC_HPP

#include <array>
#include <memory>
#include <mutex>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Models/ModelBase.hpp"
#include "DifficultyDefinition.hpp"
#include "Storages/Resource.hpp"

namespace jubeon {
	namespace game {


		//���x����typedef�B1�`10
		typedef unsigned char Level;

		class Music : public jubeon::models::ModelBase {
				
		public:
			
			//�R���X�g���N�^
			Music(std::string meta_file_path, std::string root_path);
			
			//�f�X�g���N�^
			virtual ~Music();


			//Music�̐����ƃ��[�h�𓯎��ɍs��
			//static std::shared_ptr<Music> load(const std::string meta_file_name);

			
			storages::Resource tex_title;
			storages::Resource tex_artist;
			storages::Resource tex_jacket;
			storages::Resource tex_title_bottom;
			storages::Resource tex_music_bpm;

			storages::Resource snd_shortloop;
			storages::Resource snd_music;

			
			
			//***** �A�N�Z�T *****
			//�y��ID���擾����
			int getID(void) const;

			//�m�[�c�̃t�@�C���p�X���擾����
			std::string getNotesFilePath(const Difficulty level) const;

			//bpm���擾
			std::string getBpmString(void) const;

			//���x���̎擾
			Level getLevel(const Difficulty difficulty) const;

			//�n�C�X�R�A�̎擾
			unsigned int getHighScore(const Difficulty difficulty) const;

			//�v���C�L�^�̃t�@�C���p�X�擾�i�ō��j
			std::string getHighPlayRecordFilePath(const Difficulty difficulty) const;

			//�v���C�L�^�̃t�@�C���p�X�擾�i���߁j
			std::string getLatestPlayRecordFilePath(const Difficulty difficulty) const;


			// TO DO : �폜
			//***** �y�ȑ��� *****
			//�Ȃ��Đ����鏀�����s���i�X���b�h�A���Z�[�t����Scene����̂݌Ăяo���j
			void setForPlay(void);

			//�Ȃ��Đ�����i�X���b�h�A���Z�[�t����ry
			void playSound(int wait_offset);

			//�Đ����̎��Ԃ��擾����֐��i�X���b�h�Z�[�t�j
			int getPlayingCurrentTime(void) const;
			
			//�Ȃ̒���
			unsigned int getMusicLength(void) const;

			//�Ȃ�����������j������i�X���b�h�A���Zry
			void deleteSound(void);

			//�������ɐ���������
			bool isInit(void) const;

			sf::Clock							wait_offset_ck;
		private:

			//���[�h
			virtual bool set() override;

			std::string root_path;

			//�����o�[�ϐ�(*�����Ă�����̂́Aload������̓A�N�Z�T������A���X���b�h�Z�[�t�j
			int									music_id;					//*�y��ID

			//�Ǘ����摜�x�[�X��

			//*** �m�[�c�֘A ***
			std::array<std::string, 3>			notes_filepath;				//*�m�[�c�̕��ʃt�@�C���p�X
			std::string							bpm_str;					//*�Ȃ�bpm
			std::string							decode_type;				//�m�[�c�t�@�C���̌`��	TO DO : �p���N���X������

			//*** �Ȋ֌W ***
			//const std::string					name;						//*�Ȗ�
			//const std::string					artist;						//*�A�[�e�B�X�g��
			//sf::Texture							music_name_artist;			//*�Ȗ��A�A�[�e�B�X�g���̉摜�t�@�C��
			//sf::Texture							music_name_mini;			//*�Ȗ��A�A�[�e�B�X�g���̉摜�t�@�C��
			//std::string							sound_filepath;				//*�y�ȃt�@�C���p�X
			//sf::SoundBuffer						sound_short_loop;			//*�V���[�g���[�v�p�̃o�b�t�@�̈�
			sf::Sound							sound;						// �v���C���[
			sf::Texture							thumbnail;					//*�T���l

			//*** �Q�[���֌W ***
			std::array<Level, 3>				level;						//*���x��
			std::array<unsigned int, 3>			high_score;					//*�n�C�X�R�A
			std::array<std::string, 3>			high_score_pr_filepath;		//*�v���C�L�^�t�@�C���i�ō��j�̃t�@�C���p�X
			std::array<std::string, 3>			latest_score_pr_filepath;	//*�v���C�L�^�t�@�C���i���߁j�̃t�@�C���p�X
			
			std::mutex							mtx;

			bool								is_init_success;

			int									wait_offset;

			//TO DO : MusicBar�͖���`
			//std::array<MusicBar, 3>	musicbar_challenge;	//�~���[�W�b�N�o�[�`�������W


		};
	}
}

#endif