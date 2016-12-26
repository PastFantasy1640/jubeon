//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.hpp
//////////////////////////////////////////////////////
#pragma once

#ifndef JUBEON_STORAGE_RESOURCEMANAGER_HPP
#define JUBEON_STORAGE_RESOURCEMANAGER_HPP

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>

//***** TO DO : 所持カウントが1のリソースを解放する機能を追加

namespace jubeon {
	namespace storages {



		class Resource {
		public:

			enum TYPE { TEX, FONT, SOUND };

			Resource(const Resource & cp);

			virtual ~Resource();

			bool load(void);

			bool isReady(void) const;

			std::shared_ptr<sf::Texture> gett(void);
			std::shared_ptr<sf::SoundBuffer> gets(void);
			std::shared_ptr<sf::Font> getf(void);

			void release();

			static Resource setf(const std::string filename, const TYPE type);
			static Resource seti(std::unique_ptr<sf::InputStream> * inputstream, const TYPE type);
			static Resource setk(const std::string key);

			bool setKey(const std::string key);

			//init関数を作って、設定ファイルを読み出すようにしてほしい
			//それか、initで初期化パラメータ
			//アンチエイリアスの有効無効はここでしか変えられない。
			
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



			std::shared_ptr<sf::Texture> tex_sp;
			std::shared_ptr<sf::SoundBuffer> snd_sp;
			std::shared_ptr<sf::Font> font_sp;


			unsigned int id;
			TYPE type;
			const ResourceManager * resm;

		};



	};
};



#endif