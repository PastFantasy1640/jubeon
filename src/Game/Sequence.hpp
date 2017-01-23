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
			int getHoldMarkerIndex(void) const;
			bool isHold(void) const;
			bool isHoldEnd(void) const;

		};
	
		typedef std::pair<const Note, JudgedPanelInput *> NoteJudgePair;
		typedef std::vector<NoteJudgePair> Notes;

		//Noteはconst付きメソッドのみでRead Onlyなためスレッドセーフ
		class Sequence : protected Notes{

		private:
			
			//デフォルトコンストラクタは禁止
			Sequence(void);


		public:

			Sequence(const Sequence & cp);

			//初期化
			Sequence(const std::vector<Note> notes);

			Notes::const_iterator search(const jMillisec ms) const;
			
			using Notes::const_iterator;
			using Notes::operator[];
			using Notes::at;
			using Notes::begin;
			using Notes::end;
			using Notes::size;
			using Notes::empty;

			void setJudgedPanelInput(const Notes::const_iterator target, JudgedPanelInput * judged);

		};
	}
}

#endif