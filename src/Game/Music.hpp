#pragma once

#ifndef JUBEAT_ONLINE_MUSIC_HPP
#define JUBEAT_ONLINE_MUSIC_HPP

#include <mutex>
#include <SFML/Audio.hpp>

namespace jubeat_online {
	namespace game {
		class Music {
		public:
			
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

			//スレッドセーフ対策
		//	std::mutex mtx;





		};
	}
}

#endif