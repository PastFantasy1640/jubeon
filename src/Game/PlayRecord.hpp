#pragma once

#ifndef jubeon_GAME_PLAYRECORD_HPP
#define jubeon_GAME_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <string>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "../Input/PanelInput.hpp"
#include "JudgeDefinition.hpp"

namespace jubeon {
	namespace game {

		typedef struct JudgedPanelInput : jubeon::input::PanelInput {
		public:
			Judge judge;	//ジャッジ情報が追加

			//デフォルトコンストラクタ
			JudgedPanelInput() {}

			//全指定コンストラクタ
			JudgedPanelInput(unsigned char panel_no, jubeon::input::Type t, unsigned int ms, const Judge & judge)
				: judge(judge), PanelInput(panel_no,t,ms) {}
			
			//PanelInputと組み合わせたコンストラクタ
			JudgedPanelInput(const PanelInput & panel_input, const Judge & judge)
				: PanelInput(panel_input), judge(judge) {}
		}JudgedPanelInput;

		class PlayRecord {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//判定済みを追加
			void addJudged(const jubeon::input::PanelInput p, Judge judge);
			void addJudged(const JudgedPanelInput judged_p);

			//ファイルへ書き出し(TO DO : 未実装)
			bool writeToFile(const std::string dst);

			//ファイルから読み出し(TO DO : 未実装)
			bool readFromFile(const std::string src);
			
			//リストを参照として取得する
			const std::shared_ptr<std::vector<JudgedPanelInput>> getJudgedList() const;

			//検索関数
			static std::vector<JudgedPanelInput>::const_iterator getIteratorFromTime(const std::vector<JudgedPanelInput> & list ,const int ms);

		private:
			
			
			//判定済みのリスト
			std::shared_ptr<std::vector<JudgedPanelInput>> judged_list;

		};
	}
}

#endif