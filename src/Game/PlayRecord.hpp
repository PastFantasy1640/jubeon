#pragma once

#ifndef jubeon_GAME_PLAYRECORD_HPP
#define jubeon_GAME_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "../Input/PanelInput.hpp"
#include "JudgeDefinition.hpp"

namespace jubeon {
	namespace game {

		typedef struct JudgedPanelInput : jubeon::input::PanelInput {
			Judge judge;	//ジャッジ情報が追加
		}JudgedPanelInput;

		class PlayRecord {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//判定済みを追加
			void addJudged(const jubeon::input::PanelInput & p, Judge & judge);
			void addJudged(const JudgedPanelInput & judged_p);

			//ファイルへ書き出し
			bool writeToFile(const std::string dst);

			//ファイルから読み出し
			bool readFromFile(const std::string src);
			
			//judgedlist[idx]の取得
			const JudgedPanelInput & getJudgedInput(const size_t idx) const;

			//judgedlistの指定されたmsより遅く、かつ一番近いもののconst_iteratorを返す
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputFromTime(const unsigned int ms) const;

			//judgedlistの終了イテレータ
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputListEnd(void) const;

			//judgedlistの開始イテレータ
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputListBegin(void) const;

		private:
			
			
			//判定済みのリスト
			std::vector <JudgedPanelInput> judged_list;

		};
	}
}

#endif