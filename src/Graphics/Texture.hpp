#pragma once

#ifndef JUBEON_GRAPHICS_IMAGESEQUENCER_HPP
#define JUBEON_GRAPHICS_IMAGESEQUENCER_HPP

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Systems/Logger.hpp"

namespace jubeon {
	namespace graphics {
		class Texture : protected std::vector<std::unique_ptr<sf::Texture>>{
		private:
			
			//#��A�Ԕԍ��ɕϊ�
			//hogehoge#####.png�Ƃ�
			std::string filename;

			//�ꖇ�Ɏ��܂��Ă�摜�p
			sf::Vector2u frame_count;
			sf::Vector2u bounding_size;
			unsigned int frames;
			unsigned int now_frame;

			//fps
			unsigned int fps;

			bool is_playing;

			//timer
			sf::Clock clk;

			bool is_loaded;

		public:
			
			/** �A�ԉ摜�p�R���X�g���N�^�Bfilename���w�肵�Ă��������B
			 * �A�ԂɂȂ��Ă���Ƃ����#�ɒu�����Ă��������B
			 * �Ⴆ�΁Ahoge###.png�Ȃ�Ahoge001.png�Ahoge002.png�A�ƌ������Ă����܂��B
			 * �A�Ԃ̌����ő�l(###�Ȃ�999)�ɂȂ邩�A�t�@�C�����Ȃ��Ȃ������_�œǂݍ��݂��I�����܂��B
			 * @param filenames �w�肳�ꂽ�t�H�[�}�b�g�ɑ������t�@�C����
			 * @param fps �Đ�����fps�B�W����24fps�ł��B
			 */
			Texture(const std::string filenames, const unsigned int fps = 24);
			
			/** �^�C����摜�p�R���X�g���N�^�Bfilename���w�肵�Ă��������B
			 * @param filenames �w�肳�ꂽ�t�H�[�}�b�g�ɑ������t�@�C����
			 * @param frame_count sf::Vector2u�^�ŁAx������y�����̃R�}��
			 * @param boundingbox_size sf::Vector2u�^�ŁA��R�}�̃T�C�Y
			 * @param frames �S�t���[�����Bframe_count��x��y���|�����킹������葽�����͎w��ł��܂���B
			 * @param fps �Đ�����fps�B�W����24fps�ł��B
			 */
			Texture(const std::string filename, const sf::Vector2u & frame_count, const sf::Vector2u & boundingbox_size, const unsigned int frames, const unsigned int fps = 24);

			/** �A�ԉ摜�A�^�C����摜�����[�h���AGPU�������ɕێ����܂��B
			 * @returns �����A�������͂��łɐ���Ƀ��[�h����Ă���Ƃ���true�B���s�����Ƃ���false�B
			 */
			bool load();

			/** �A�ԉ摜�A�^�C����摜������������j�����܂��B
			 */
			void unload();


			//######### �A�N�Z�T ###########
			inline int getFPS() const;
			inline void setFPS(const unsigned int fps);

			inline int getNowFrame() const;
			inline void seekNowFrame(const unsigned int to);

			inline bool isLoaded() const;

			virtual ~Texture();

			//######## ���� #########
			void start();
			void startFromHead();
			void stop();

			//######## �`�� #########
			const sf::Texture * getTexture() const;

		};
	}
}

#endif
