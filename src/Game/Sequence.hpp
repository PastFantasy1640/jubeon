#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include "Note.hpp"


namespace jubeat_online {
	namespace game {
		class Sequence {

			//譜面本体
			std::vector<Note> notes;
			std::vector<HoldNote> hold_notes;

			//譜面名
			std::string filename;

			//デフォルトコンストラクタは禁止
			Sequence();

			//コピーコンストラクタも禁止。
			Sequence(const Sequence & cp);

			//ロードしたか
			bool is_loaded;

		public:

			//初期化
			//ロードまではしない
			Sequence(const std::string & filename);

			//譜面のロード
			bool load(void);

			//譜面の破棄
			void deleteNotes(void);

			//getアクセサ
			const std::vector<Note> * getNotes() const;
			const std::vector<HoldNote> * getHoldNote() const;
			std::string getNotesFileName(void) const;

			//ロードしたか
			bool isLoad(void) const;
			
		};
	}
}

#endif