#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <memory>
#include <fstream>
#include <unordered_map>

#include "JudgeDefinition.hpp"

#include <SFML/Graphics.hpp>

//For Read JSON
//�����ꂢ���������FileStorages���Model���ɒu�������
#include "../Systems/picojson.hpp"

namespace jubeon {
	namespace game {
		class Marker {
		private:

			//STL��public�p��NG
			class MarkerTextures : protected std::vector<std::unique_ptr<sf::Texture>> {
			private:

				const unsigned int duration;
				const int id;

				MarkerTextures();	//����`
			public:
				MarkerTextures(const int id, const unsigned int duration);

				int getID() const;

				unsigned int getDuration() const;

				const sf::Texture * getTexture(const int diff_ms) const;

				using std::vector<std::unique_ptr<sf::Texture>>::push_back;
			};

			
			//�֘A�t��
			std::unordered_map<std::string, std::unique_ptr<sf::Image>> images_;

			//�}�[�J�[�Ɋւ��Ẵ��^�f�[�^�������Ă�t�@�C���̃p�X
			std::string meta_filepath;

			//�f�B���N�g����
			std::string directory;

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
			Marker(const std::string directory, const std::string meta_filepath);
			
			//�f�X�g���N�^
			virtual ~Marker();

			//���[�h�Btrue�Ő���
			bool load(void);

			unsigned int getLengthBefore() const;
			unsigned int getLengthAfterMax() const;

			//���Ԃ��w�肵�ēK�؂ȃe�N�X�`����Ԃ��֐�
			//�}�C�i�X���w�肵���ꍇ��appear
			const sf::Texture * getTexturePtr(const int diff_ms, const jubeon::Judge judge) const;


		};

	}
}

#endif
