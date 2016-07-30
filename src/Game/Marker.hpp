#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "../Systems/picojson.hpp"

namespace jubeat_online {
	namespace game {
		class Marker {
		private:

			//STL��public�p��NG
			class MarkerTextures : protected std::vector<std::unique_ptr<sf::Texture>> {
			private:
				unsigned int duration;
				int id;

				MarkerTextures();
			public:
				MarkerTextures(int id, unsigned int duration);

				int getID();

				using std::vector<std::unique_ptr<sf::Texture>>::push_back;
			};



			//�}�[�J�[�Ɋւ��Ẵ��^�f�[�^�������Ă�t�@�C���̃p�X
			std::string meta_filepath;

			//�}�[�J�[��
			std::string marker_name;
			
			typedef std::shared_ptr<MarkerTextures> SPMarkerTextures;

			//�o���̃}�[�J�[�摜�Q
			SPMarkerTextures appear;

			//���ł̃}�[�J�[�摜�Q
			std::array<SPMarkerTextures , 6> disappear;

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