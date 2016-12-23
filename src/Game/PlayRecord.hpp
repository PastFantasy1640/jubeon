#pragma once

#ifndef jubeon_GAME_PLAYRECORD_HPP
#define jubeon_GAME_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Input/PanelInput.hpp"
#include "JudgeDefinition.hpp"
#include "Game/TypeDefinition.hpp"

#include "Sequence.hpp"

namespace jubeon {
	namespace game {

		typedef struct JudgedPanelInput : jubeon::input::PanelInput {
		public:
			Judge judge;	//ジャッジ情報が追加


			//全指定コンストラクタ
			JudgedPanelInput(unsigned char panel_no, jubeon::Type t, unsigned int ms, const Judge & judge)
				: judge(judge), PanelInput(panel_no,t,ms) {}
			
			//PanelInputと組み合わせたコンストラクタ
			JudgedPanelInput(const PanelInput & panel_input, const Judge & judge)
				: PanelInput(panel_input), judge(judge) {}
		}JudgedPanelInput;

		class PlayRecord : protected std::vector<JudgedPanelInput> {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//判定済みを追加
			//void addJudged(const jubeon::input::PanelInput p, Judge judge, const Sequence::const_iterator<Note> & note);
			//void addJudged(const JudgedPanelInput judged_p);

			//Judge
			void judge(const Sequence & seq, const input::PanelInput panel_input);


			//ファイルへ書き出し(TO DO : 未実装)
			bool writeToFile(const std::string dst) const;

			//ファイルから読み出し(TO DO : 未実装)
			bool readFromFile(const std::string src);
			
			
			//検索関数
			std::vector<JudgedPanelInput>::const_iterator getIteratorFromTime(const int ms);


			using std::vector<JudgedPanelInput>::const_iterator;
			using std::vector<JudgedPanelInput>::begin;
			using std::vector<JudgedPanelInput>::end;
			using std::vector<JudgedPanelInput>::size;
			using std::vector<JudgedPanelInput>::at;
			using std::vector<JudgedPanelInput>::empty;
			using std::vector<JudgedPanelInput>::operator[];

		private:
			
			std::string name;
			std::string date;
			
			//判定済みのリスト
			//std::shared_ptr<std::vector<JudgedPanelInput>> judged_list;

		};
	}
}

#endif