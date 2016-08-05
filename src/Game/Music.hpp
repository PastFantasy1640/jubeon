#pragma once

#ifndef JUBEON_GAME_MUSIC_HPP
#define JUBEON_GAME_MUSIC_HPP

#include <array>
#include <memory>
#include <mutex>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace game {

		//難易度を表す列挙型
		typedef enum Difficulty : size_t {
			BASIC = 0,
			ADVANCED = 1,
			EXTREME = 2
		}Level;

		//レベルのtypedef。1～10
		typedef unsigned char Level;

		class Music {
		public:
			
			//コンストラクタ
			Music(const std::string meta_filepath);

			//デストラクタ
			virtual ~Music();

			//ロードを行う
			bool load(void);


			//***** アクセサ *****
			//楽曲IDを取得する
			int getID(void) const;

			//ノーツのファイルパスを取得する
			std::string getNotesFilePath(const Difficulty level) const;

			//bpmのテクスチャを取得
			const sf::Texture & getBpmTexture(void) const;

			//曲名、アーティスト名の画像ファイル
			const sf::Texture & getMusicNameAndArtistTexture(void) const;

			//曲名の下画面用画像ファイル
			const sf::Texture & getMusicNameTexture(void) const;

			//ショートループ用の曲データを取得
			const sf::SoundBuffer & getSoundForShortLoop(void) const;

			//サムネイルを取得
			const sf::Texture & getThumbnailTexture(void) const;

			//レベルの取得
			Level getLevel(const Difficulty difficulty) const;

			//ハイスコアの取得
			unsigned int getHighScore(const Difficulty difficulty) const;

			//プレイ記録のファイルパス取得（最高）
			std::string getHighPlayRecordFilePath(const Difficulty difficulty) const;

			//プレイ記録のファイルパス取得（直近）
			std::string getLatestPlayRecordFilePath(const Difficulty difficulty) const;


			//***** 楽曲操作 *****
			//曲を再生する準備を行う（スレッドアンセーフだがSceneからのみ呼び出し）
			void setForPlay(void);

			//曲を再生する（スレッドアンセーフだがry
			void playSound(void);

			//再生中の時間を取得する関数（スレッドセーフ）
			unsigned int getPlayingCurrentTime(void) const;

			//曲をメモリから破棄する（スレッドアンセry
			void deleteSound(void);

		private:

			//メンバー変数(*がついているものは、loadした後はアクセサがあり、かつスレッドセーフ）
			int									music_id;					//*楽曲ID
			const std::string					metafile_path;				//メタファイルパス

			//管理を画像ベースに

			//*** ノーツ関連 ***
			std::array<std::string, 3>			notes_filepath;				//*ノーツの譜面ファイルパス
			sf::Texture							bpm_texture;				//*曲のbpmが記された画像

			//*** 曲関係 ***
			//const std::string					name;						//*曲名
			//const std::string					artist;						//*アーティスト名
			sf::Texture							music_name_artist;			//*曲名、アーティスト名の画像ファイル
			sf::Texture							music_name_mini;			//*曲名、アーティスト名の画像ファイル
			std::string							sound_filepath;				//*楽曲ファイルパス
			sf::SoundBuffer						sound_short_loop;			//*ショートループ用のバッファ領域
			std::unique_ptr<sf::SoundBuffer>	up_sound_buffer;			//*バッファ
			sf::Sound							sound;						// プレイヤー
			sf::Texture							thumbnail;					//*サムネ

			//*** ゲーム関係 ***
			std::array<Level, 3>				level;						//*レベル
			std::array<unsigned int, 3>			high_score;					//*ハイスコア
			std::array<std::string, 3>			high_score_pr_filepath;		//*プレイ記録ファイル（最高）のファイルパス
			std::array<std::string, 3>			latest_score_pr_filepath;	//*プレイ記録ファイル（直近）のファイルパス


			std::mutex							mtx;

			//TO DO : MusicBarは未定義
			//std::array<MusicBar, 3>	musicbar_challenge;	//ミュージックバーチャレンジ
			

			//例のごとくデフォルトコンストラクタは禁止。
			Music(void);
		};
	}
}

#endif