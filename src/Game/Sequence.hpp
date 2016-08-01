#pragma once

#ifndef JUBEAT_ONLINE_SEQUENCE_HPP
#define JUBEAT_ONLINE_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>


namespace jubeat_online {
	namespace game {
		
		typedef struct Note {
			int justTime;
			int panelIndex;
			int duration;
			Note()
				: justTime(0),
				panelIndex(0),
				duration(0) {};
		} Note;

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