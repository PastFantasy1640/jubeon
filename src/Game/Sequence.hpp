#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"
#include "NoteDefinition.hpp"
#include "JudgedPanelInput.hpp"

namespace jubeon {
	namespace game {
		
		//Noteはconst付きメソッドのみでRead Onlyなためスレッドセーフ
		class Note{


		private:

			//デフォルトコンストラクタは禁止
			Note();

			void operator=(Note & n);


		protected:
			
			//ジャストタイム(ms)
			const jMillisec justTime;

			//パネル番号(0-15)
			const jPanel panelIndex;

			//ホールドの時間(0の場合はタッチ譜面）
			const jMillisec duration;

			//ホールドマーカーの出現位置パネル
			//0xffの場合はホールドマーカー終了地点
			//isHoldはtrue、isHoldEndもtrueになる。
			const jPanel holdMarkerIndex;

		public:
			
			static const jPanel HOLD_END = 0xFF;

			//普通のマーカーのコンストラクタ
			Note(const jMillisec just_time, const jPanel panel_idx, const bool is_hold_end = false);

			//ホールドマーカーのコンストラクタ
			Note(const jMillisec just_time, const jPanel panel_idx, const int duration, const int holdmarker_panel_idx);


			//アクセサ
			int getJustTime(void) const;
			int getPanelIndex(void) const;
			int getHoldDuration(void) const;
			int getHoldEndTime(void) const;
			int getHoldMarkerIndex(void) const;
			bool isHold(void) const;
			bool isHoldEnd(void) const;

		};
	
		typedef std::pair<const Note, JudgedPanelInput *> NoteJudgePair;
		class Notes : protected std::vector<NoteJudgePair> {
		protected:
		public:
			using std::vector<NoteJudgePair>::const_iterator;
			using std::vector<NoteJudgePair>::operator[];
			using std::vector<NoteJudgePair>::at;
			using std::vector<NoteJudgePair>::begin;
			using std::vector<NoteJudgePair>::end;
			using std::vector<NoteJudgePair>::size;
			using std::vector<NoteJudgePair>::empty;
			Notes::const_iterator jubeon::game::Notes::search(const jMillisec ms) const;
		};

		//Noteはconst付きメソッドのみでRead Onlyなためスレッドセーフ
		class Sequence : public Notes{

		private:
			
			//デフォルトコンストラクタは禁止
			Sequence(void);


		public:

			Sequence(const Sequence & cp);

			//初期化
			Sequence(const std::vector<Note> notes);
			
			void setJudgedPanelInput(const Notes::const_iterator target, JudgedPanelInput * judged);

		};
	}
}

#endif