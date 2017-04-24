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
			
			//Sequence用
			std::size_t frames;
			std::size_t start;

			//Tile用
			sf::Vector2u size;
			sf::Vector2u tilecount;
			
		};

		class Resource {
		
		public:
			
			/** Resource::引数付きコンストラクタ
			 * リソースの本体を取得します。
			 * 指定されたタグが登録されていない場合に、ResourceTagNotFoundExceptionをthrowします。
			 * @param tag 指定するリソースのタグ
			 * @throw ResourceTagNotFoundException 指定されたタグが見つからないとthrowされます。
			 */
			Resource(const std::string tag) throw (ResourceTagNotFoundException);
			
			/** Resource::コピーコンストラクタ
			 * コピーコンストラクタです
			 * @param copy コピー元のインスタンス
			 */
			Resource(const Resource & copy) throw ();


			/** static Resource::store関数
			 * リソースをjsonから登録します。
			 * jsonにてつけたタグを元に、指定されたタグのみを登録します。
			 * 指定されたタグに関して、存在していなかった場合（jsonに不備があった場合）ログを出力します。
			 * 更に、用意されたタグが、すでに有るものや同じjsonの中で重複していた場合、ResourceTagDupricateExceptionを投げます。
			 * @param json リソース定義のJsonクラス
			 * @param tag リソースに定義したタグ。"*"を指定すると、jsonの中身全てを登録します。
			 * @throw ResourceTagDupricateException タグが重複するとthrowされます
			 */
			static void store(const wlib::Json & json, const std::string tag = "*") throw (ResourceTagDupricateException);
			
			/** Resource::load関数
			 * リソースをロードし、メモリ上へ読み込みます。
			 * すでにロードされている場合などはスキップされます。
			 * @return trueなら成功、falseなら失敗
			 */
			bool load(void) throw ();

			/** Resource::getTexture関数
			 * 指定するタグのリソースを取得します
			 * @return リソースのポインタ。絶対にdeleteをしないでください。
			 */
			graphics::Texture * getTexture(void) throw ();

			/** Resource::getSound関数
			 * 指定するタグのリソースを取得します
			 * @return リソースのポインタ。絶対にdeleteをしないでください。
			 */
			sf::SoundBuffer * getSound(void) throw ();

			/** Resource::getFont関数
			 * 指定するタグのリソースを取得します
			 * @return リソースのポインタ。絶対にdeleteをしないでください。
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