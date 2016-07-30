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

			//STLはpublic継承NG
			class MarkerTextures : private std::vector<sf::Texture> {
			private:
				

			public:
				MarkerTextures();
				virtual ~MarkerTextures();


			};

			//マーカーに関してのメタデータが入ってるファイルのパス
			std::string meta_filepath;

			//マーカー名
			std::string marker_name;
			
			typedef std::shared_ptr<MarkerTextures> SPMarkerTextures;

			//出現のマーカー画像群
			SPMarkerTextures appear;

			//消滅のマーカー画像群
			std::array<SPMarkerTextures , 7> disappear;

			//例によってデフォルトコンストラクタは禁止
			Marker();

		public:

			//コンストラクタ。ロードはしない
			Marker(const std::string meta_filepath);
			
			//デストラクタ
			virtual ~Marker();

			//ロード。trueで成功
			bool load(void);


		};

	}
}

#endif