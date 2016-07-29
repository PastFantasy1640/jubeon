#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace game {
		class Marker {
		private:

			//STL��public�p��NG
			class MarkerTexture : private std::vector<sf::Texture> {
			private:
				

			public:
				MarkerTexture();
				virtual ~MarkerTexture();


			};

			//�}�[�J�[�Ɋւ��Ẵ��^�f�[�^�������Ă�t�@�C���̃p�X
			std::string meta_filepath;

			//�}�[�J�[��
			std::string marker_name;
			
			//�o���̃}�[�J�[�摜�Q
			MarkerTexture appear;
			std::array<MarkerTexture, 7> disappear;

			//��ɂ���ăf�t�H���g�R���X�g���N�^�͋֎~
			Marker();

		public:

			//�R���X�g���N�^�B���[�h�͂��Ȃ�
			Marker(const std::string meta_filepath);
			
			//�f�X�g���N�^
			virtual ~Marker();

			//���[�h�Btrue�Ő���
			bool load(void);


		};

	}
}

#endif