#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"


namespace jubeat_online {
	namespace game {

		class Note{

		private:

			//デフォルトコンストラクタは禁止
			Note();

		protected:
			
			//ジャストタイム(ms)
			int justTime;

			//パネル番号(0-15)
			int panelIndex;

			//ホールドの時間
			int duration;

			//ホールドマーカーの出現位置パネル
			int holdMarkerIndex;

			//このノートに対する判定
			std::shared_ptr<PlayRecord::PanelInput> judged;
			
		public:
			
			//普通のマーカーのコンストラクタ
			Note(const int just_time, const int panel_idx);

			//ホールドマーカーのコンストラクタ
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx);

			//ホールドマーカーのコンストラクタ
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx, const std::shared_ptr<PanelInput> judge);

			//アクセサ
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldMarkerIndex(void) const;

			//ジャッジ
			void getJudge(int * ms_diff, Judge * judge) const;
			
		};

		typedef std::vector<Note> Notes;
		typedef std::shared_ptr<Notes> SPNotes;

		class Sequence {

		private:
			//譜面本体
			SPNotes notes;
			
			//デフォルトコンストラクタは禁止
			Sequence();

			//コピーコンストラクタも禁止。
			Sequence(const Sequence & cp);

		public:

			//初期化
			//ロードまではしない
			Sequence(const std::vector<Note> notes);
			
			//ノートを取得
			SPNotes getNotes(void);
			
		};
	}
}

#endif