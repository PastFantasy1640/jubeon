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
			
			//#を連番番号に変換
			//hogehoge#####.pngとか
			std::string filename;

			//一枚に収まってる画像用
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
			
			/** 連番画像用コンストラクタ。filenameを指定してください。
			 * 連番になっているところを#に置換してください。
			 * 例えば、hoge###.pngなら、hoge001.png、hoge002.png、と検索していきます。
			 * 連番の桁が最大値(###なら999)になるか、ファイルがなくなった時点で読み込みを終了します。
			 * @param filenames 指定されたフォーマットに則ったファイル名
			 * @param fps 再生するfps。標準は24fpsです。
			 */
			Texture(const std::string filenames, const unsigned int fps = 24);
			
			/** タイル状画像用コンストラクタ。filenameを指定してください。
			 * @param filenames 指定されたフォーマットに則ったファイル名
			 * @param frame_count sf::Vector2u型で、x方向とy方向のコマ数
			 * @param boundingbox_size sf::Vector2u型で、一コマのサイズ
			 * @param frames 全フレーム数。frame_countのxとyを掛け合わせた数より多い数は指定できません。
			 * @param fps 再生するfps。標準は24fpsです。
			 */
			Texture(const std::string filename, const sf::Vector2u & frame_count, const sf::Vector2u & boundingbox_size, const unsigned int frames, const unsigned int fps = 24);

			/** 連番画像、タイル状画像をロードし、GPUメモリに保持します。
			 * @returns 成功、もしくはすでに正常にロードされているときはtrue。失敗したときはfalse。
			 */
			bool load();

			/** 連番画像、タイル状画像をメモリから破棄します。
			 */
			void unload();


			//######### アクセサ ###########
			inline int getFPS() const;
			inline void setFPS(const unsigned int fps);

			inline int getNowFrame() const;
			inline void seekNowFrame(const unsigned int to);

			inline bool isLoaded() const;

			virtual ~Texture();

			//######## 操作 #########
			void start();
			void startFromHead();
			void stop();

			//######## 描画 #########
			const sf::Texture * getTexture() const;

		};
	}
}

#endif
