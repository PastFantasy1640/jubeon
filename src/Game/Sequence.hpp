#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"

namespace jubeon {
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

			//ホールドの時間(0の場合はタッチ譜面）
			int duration;

			//ホールドマーカーの出現位置パネル
			int holdMarkerIndex;

			
		public:
			
			//普通のマーカーのコンストラクタ
			Note(const int just_time, const int panel_idx);

			//ホールドマーカーのコンストラクタ
			Note(const int just_time, const int panel_idx, const int duration, const int holdmarker_panel_idx);


			//アクセサ
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldMarkerIndex(void) const;
			bool isHold(void) const;

			
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
			Sequence(const SPNotes notes);
			
			//ノートを取得
			SPNotes getNotes(void);

			Note operator[] (const size_t idx);
			
		};
	}
}

#endif