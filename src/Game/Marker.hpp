#pragma once

#ifndef JUBEON_GAME_MARKER_HPP
#define JUBEON_GAME_MARKER_HPP

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace game {
		class Marker {
		private:

			//STLはpublic継承NG
			class MarkerTexture : private std::vector<sf::Texture> {
			private:
				

			public:
				MarkerTexture();
				virtual ~MarkerTexture();


			};

			//マーカーに関してのメタデータが入ってるファイルのパス
			std::string meta_filepath;

			//マーカー名
			std::string marker_name;
			
			//出現のマーカー画像群
			MarkerTexture appear;
			std::array<MarkerTexture, 7> disappear;

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