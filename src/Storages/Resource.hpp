//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.hpp
//////////////////////////////////////////////////////
#pragma once

#ifndef JUBEON_STORAGE_RESOURCEMANAGER_HPP
#define JUBEON_STORAGE_RESOURCEMANAGER_HPP

#include <memory>

#include "Graphics/Texture.hpp"
#include "Models/wlib_Json.hpp"
#include <SFML/Audio.hpp>

#include <unordered_map>
#include <exception>


namespace jubeon {
	namespace storages {

		
		class ResourceTagDupricateException : public std::invalid_argument {
		public:
			ResourceTagDupricateException(const std::string tag) throw () : std::invalid_argument("Dupricating Resource Tag : " + tag) {}
			virtual ~ResourceTagDupricateException() {}
		};
		
		class ResourceTagNotFoundException : public std::out_of_range {
		public:
			ResourceTagNotFoundException(const std::string tag) throw () : std::out_of_range("The tag is not found. [tag]" + tag) {}
			virtual ~ResourceTagNotFoundException() {}
		};


		class ResourceMeta {
		public:
			
			std::string name;
			std::string type;
			std::string filename;
			
			//Sequence�p
			std::size_t frames;
			std::size_t start;

			//Tile�p
			sf::Vector2u size;
			sf::Vector2u tilecount;
			
		};

		class Resource {
		
		public:
			
			/** Resource::�����t���R���X�g���N�^
			 * ���\�[�X�̖{�̂��擾���܂��B
			 * �w�肳�ꂽ�^�O���o�^����Ă��Ȃ��ꍇ�ɁAResourceTagNotFoundException��throw���܂��B
			 * @param tag �w�肷�郊�\�[�X�̃^�O
			 * @throw ResourceTagNotFoundException �w�肳�ꂽ�^�O��������Ȃ���throw����܂��B
			 */
			Resource(const std::string tag) throw (ResourceTagNotFoundException);
			
			/** Resource::�R�s�[�R���X�g���N�^
			 * �R�s�[�R���X�g���N�^�ł�
			 * @param copy �R�s�[���̃C���X�^���X
			 */
			Resource(const Resource & copy) throw ();


			/** static Resource::store�֐�
			 * ���\�[�X��json����o�^���܂��B
			 * json�ɂĂ����^�O�����ɁA�w�肳�ꂽ�^�O�݂̂�o�^���܂��B
			 * �w�肳�ꂽ�^�O�Ɋւ��āA���݂��Ă��Ȃ������ꍇ�ijson�ɕs�����������ꍇ�j���O���o�͂��܂��B
			 * �X�ɁA�p�ӂ��ꂽ�^�O���A���łɗL����̂⓯��json�̒��ŏd�����Ă����ꍇ�AResourceTagDupricateException�𓊂��܂��B
			 * @param json ���\�[�X��`��Json�N���X
			 * @param tag ���\�[�X�ɒ�`�����^�O�B"*"���w�肷��ƁAjson�̒��g�S�Ă�o�^���܂��B
			 * @throw ResourceTagDupricateException �^�O���d�������throw����܂�
			 */
			static void store(const wlib::Json & json, const std::string tag = "*") throw (ResourceTagDupricateException);
			
			/** Resource::load�֐�
			 * ���\�[�X�����[�h���A��������֓ǂݍ��݂܂��B
			 * ���łɃ��[�h����Ă���ꍇ�Ȃǂ̓X�L�b�v����܂��B
			 * @return true�Ȃ琬���Afalse�Ȃ玸�s
			 */
			bool load(void) throw ();

			/** Resource::getTexture�֐�
			 * �w�肷��^�O�̃��\�[�X���擾���܂�
			 * @return ���\�[�X�̃|�C���^�B��΂�delete�����Ȃ��ł��������B
			 */
			graphics::Texture * getTexture(void) throw ();

			/** Resource::getSound�֐�
			 * �w�肷��^�O�̃��\�[�X���擾���܂�
			 * @return ���\�[�X�̃|�C���^�B��΂�delete�����Ȃ��ł��������B
			 */
			sf::SoundBuffer * getSound(void) throw ();

			/** Resource::getFont�֐�
			 * �w�肷��^�O�̃��\�[�X���擾���܂�
			 * @return ���\�[�X�̃|�C���^�B��΂�delete�����Ȃ��ł��������B
			 */
			sf::Font * getFont(void) throw ();


		private:
			Resource();

			std::shared_ptr<graphics::Texture> texture;
			std::shared_ptr<sf::SoundBuffer> sound;
			std::shared_ptr<sf::Font> font;

			static 


		
		};



		/*
		class Resource {
		public:

			enum TYPE { TEX, FONT, SOUND };

			Resource(const Resource & cp);

			virtual ~Resource();

			bool load(void);

			bool isReady(void) const;

			std::shared_ptr<jubeon::graphics::ImageSequencer> getseq(void);
			//std::shared_ptr<sf::Texture> gett(void);
			std::shared_ptr<sf::SoundBuffer> gets(void);
			std::shared_ptr<sf::Font> getf(void);

			void release();
			
			static Resource setjson(const wlib::Json & json, const std::string name);
			static Resource set(std::shared_ptr<graphics::ImageSequencer> instance);
			//static Resource set(std::shared_ptr<sf::Texture> instance);
			static Resource set(std::shared_ptr<sf::SoundBuffer> instance);
			static Resource set(std::shared_ptr<sf::Font> instance);
			
			//static Resource setf(const std::string filename, const TYPE type);
			//static Resource seti(std::unique_ptr<sf::InputStream> * inputstream, const TYPE type);
			//static Resource setk(const std::string key);

			bool setKey(const std::string key);

			//init�֐�������āA�ݒ�t�@�C����ǂݏo���悤�ɂ��Ăق���
			//���ꂩ�Ainit�ŏ������p�����[�^
			//�A���`�G�C���A�X�̗L�������͂����ł����ς����Ȃ��B
			
			void operator=(Resource p);
			Resource();
			Resource(const unsigned int id, const TYPE type);

		private:

			class ResourceManager {
			public:

				~ResourceManager();

				unsigned int getNextID();

				static ResourceManager * getInstance();

				std::unordered_map<unsigned int, std::string> filename_map;
				std::unordered_map<std::string, unsigned int> filename_map_id;
				std::unordered_map<unsigned int, std::unique_ptr<sf::InputStream>> inputstream_map;
				std::unordered_map<sf::InputStream *, unsigned int> inputstream_map_id;

				std::unordered_map<unsigned int, std::shared_ptr<sf::Texture>> textures;
				std::unordered_map<unsigned int, std::shared_ptr<sf::Font>> fonts;
				std::unordered_map<unsigned int, std::shared_ptr<sf::SoundBuffer>> sounds;

				std::unordered_map<std::string, Resource> key_map;

				

			private:

				static std::unique_ptr<ResourceManager> instance;

				ResourceManager();

				unsigned int nID;


			};

			wlib::Json json;

			std::shared_ptr<sf::Texture> tex_sp;
			std::shared_ptr<sf::SoundBuffer> snd_sp;
			std::shared_ptr<sf::Font> font_sp;


			unsigned int id;
			TYPE type;
			const ResourceManager * resm;

		};

		*/

	};
};



#endif