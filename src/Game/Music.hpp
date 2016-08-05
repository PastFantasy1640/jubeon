#pragma once

#ifndef jubeon_MUSIC_HPP
#define jubeon_MUSIC_HPP

#include <array>
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {
		class Music {
		public:
			
			//コンストラクタ
			Music(




			//再生中の時間を取得する関数（スレッドセーフ）
			unsigned int getPlayingCurrentTime(void) const;

			//再生を開始する
			void startToPlay(void);

			//セレクトミュージック用に再生する。指定されたとおりにFI、FOする
			void startToPlayForSM(void);

			//****TO DO : 今だけ、public領域
			//曲データ
			sf::SoundBuffer soundbuffer;
			//プレイヤー
			sf::Sound soundplayer;
		private:

			//メンバー変数
			int									music_id;					//楽曲ID
			const std::string					metafile_path;				//メタファイルパス
			std::array<std::string, 3>			notes_filepath;				//ノーツの譜面ファイルパス
			std::array<int, 3>					high_score;					//ハイスコア
			std::array<std::string, 3>	high_score_pr_filepath;		//プレイ記録ファイル（最高）のファイルパス
				
			std::array<std::string, 3>	latest_score_pr_filepath;	//プレイ記録ファイル（直近）のファイルパス

			const std::string					name;						//曲名
			const std::string					artist;						//アーティスト名
			const std::string					sound_filepath;				//楽曲ファイルパス

			std::unique_ptr<sf::SoundBuffer>	up_sound_buffer;			//バッファ
			const sf::Sound						sound;						//プレイヤー
			const sf::Image						thumbnail;					//サムネ
			
			//TO DO : MusicBarは未定義
			//std::array<MusicBar, 3>	musicbar_challenge;	//ミュージックバーチャレンジ
			

			//例のごとくデフォルトコンストラクタは禁止。
			Music(void);
		};
	}
}

#endif