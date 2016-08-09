#pragma once

#ifndef jubeon_SEQUENCE_HPP
#define jubeon_SEQUENCE_HPP

#include <vector>
#include <string>
#include <memory>
#include "JudgeDefinition.hpp"

namespace jubeon {
	namespace game {
		
		//Noteはconst付きメソッドのみでRead Onlyなためスレッドセーフ
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
			/*
			bool operator == (Note n) { 
				return (n.duration == this->duration
					&& n.holdMarkerIndex == this->holdMarkerIndex
					&& n.justTime == this->justTime
					&& n.panelIndex == this->panelIndex);
			}*/
			
		};
		
		//Noteはconst付きメソッドのみでRead Onlyなためスレッドセーフ
		class Sequence : protected std::vector<Note>{

		private:
			
			//デフォルトコンストラクタは禁止
			Sequence(void);

			//コピーコンストラクタも禁止。
			Sequence(const Sequence & cp);

		public:

			//初期化
			Sequence(const std::vector<Note> notes);
			
			const Note & operator[] (size_t idx) const;

			const Note & at(size_t idx) const;

			std::vector<Note>::const_iterator begin() const;

			std::vector<Note>::const_iterator end() const;

			std::vector<Note>::const_iterator search(const int ms) const;

			std::size_t size() const;
		};
	}
}

#endif