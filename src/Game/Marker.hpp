#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace game {
		class Marker {
		private:

			//STL��public�p��NG
			class MarkerTextures : private std::vector<sf::Texture> {
			private:
				

			public:
				MarkerTextures();
				virtual ~MarkerTextures();


			};

			//�}�[�J�[�Ɋւ��Ẵ��^�f�[�^�������Ă�t�@�C���̃p�X
			std::string meta_filepath;

			//�}�[�J�[��
			std::string marker_name;
			
			typedef std::shared_ptr<MarkerTextures> SPMarkerTextures;

			//�o���̃}�[�J�[�摜�Q
			SPMarkerTextures appear;

			//���ł̃}�[�J�[�摜�Q
			std::array<SPMarkerTextures , 7> disappear;

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