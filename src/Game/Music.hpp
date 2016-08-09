#pragma once

#ifndef JUBEON_GAME_MUSIC_HPP
#define JUBEON_GAME_MUSIC_HPP

#include <array>
#include <memory>
#include <mutex>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Models/ModelBase.hpp"

namespace jubeon {
	namespace game {

		//難易度を表す列挙型
		typedef enum Difficulty : size_t {
			BASIC = 0,
			ADVANCED = 1,
			EXTREME = 2
		}Difficulty;

		//レベルのtypedef。1～10
		typedef unsigned char Level;

		class Music : protected jubeon::models::ModelBase {
				
		public:

			Music(std::string meta_file_path);
			
			//デストラクタ
			virtual ~Music();

			//Musicの生成とロードを同時に行う
			static std::shared_ptr<Music> load(const std::string meta_file_name);

			//***** アクセサ *****
			//楽曲IDを取得する
			int getID(void) const;

			//ノーツのファイルパスを取得する
			std::string getNotesFilePath(const Difficulty level) const;

			//bpmのテクスチャを取得
			std::string getBpm(void) const;

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
			void playSound(int wait_offset);

			//再生中の時間を取得する関数（スレッドセーフ）
			int getPlayingCurrentTime(void) const;

			//曲をメモリから破棄する（スレッドアンセry
			void deleteSound(void);

			//初期化に成功したか
			bool isInit(void) const;

			sf::Clock							wait_offset_ck;
		private:

			//メンバー変数(*がついているものは、loadした後はアクセサがあり、かつスレッドセーフ）
			int									music_id;					//*楽曲ID
			std::string							metafile_path;				//メタファイルパス

			//管理を画像ベースに

			//*** ノーツ関連 ***
			std::array<std::string, 3>			notes_filepath;				//*ノーツの譜面ファイルパス
			std::string							bpm_string;					//*曲のbpm
			std::string							decode_type;				//ノーツファイルの形式	TO DO : 継承クラスを実装

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

			bool								is_init_success;

			int									wait_offset;

			//TO DO : MusicBarは未定義
			//std::array<MusicBar, 3>	musicbar_challenge;	//ミュージックバーチャレンジ

			virtual picojson::value GetJsonValue() override;

			void set(const int music_id, const std::string meta_file_name);

			virtual bool Init(picojson::value val) override;

		};
	}
}

#endif