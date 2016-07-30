#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <memory>
#include <fstream>

#include "JudgeDefinition.hpp"

#include <SFML/Graphics.hpp>

#include "../Systems/picojson.hpp"

namespace jubeat_online {
	namespace game {
		class Marker {
		private:

			//STLはpublic継承NG
			class MarkerTextures : protected std::vector<std::unique_ptr<sf::Texture>> {
			private:
				unsigned int duration;
				int id;

				MarkerTextures();
			public:
				MarkerTextures(int id, unsigned int duration);

				int getID();

				const sf::Texture * getTexture(const int diff_ms) const;

				using std::vector<std::unique_ptr<sf::Texture>>::push_back;
			};



			//マーカーに関してのメタデータが入ってるファイルのパス
			std::string meta_filepath;

			//ディレクトリ名
			std::string directory;

			//マーカー名
			std::string marker_name;
			
			typedef std::shared_ptr<MarkerTextures> SPMarkerTextures;

			//出現のマーカー画像群
			SPMarkerTextures appear;

			//消滅のマーカー画像群
			std::array<SPMarkerTextures , 6> disappear;

			//例によってデフォルトコンストラクタは禁止
			Marker();

		public:

			//コンストラクタ。ロードはしない
			Marker(const std::string directory, const std::string meta_filepath);
			
			//デストラクタ
			virtual ~Marker();

			//ロード。trueで成功
			bool load(void);

			//時間を指定して適切なテクスチャを返す関数
			//マイナスを指定した場合はappear
			const sf::Texture * getTexturePtr(const int diff_ms, const jubeat_online::game::Judge judge) const;


		};

	}
}

#endif