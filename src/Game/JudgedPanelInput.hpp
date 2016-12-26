#pragma once

#ifndef JUBEON_GAME_JUDGEDPANELINPUT_HPP
#define JUBEON_GAME_JUDGEDPANELINPUT_HPP

#include "JudgeDefinition.hpp"
#include "Input/PanelInput.hpp"

namespace jubeon {
	namespace game {

		typedef struct JudgedPanelInput : jubeon::input::PanelInput {
		public:
			const Judge judge;	//ジャッジ情報が追加

								//全指定コンストラクタ
			JudgedPanelInput(unsigned char panel_no, jubeon::Type t, unsigned int ms, const Judge & judge)
				: judge(judge), PanelInput(panel_no, t, ms) {}

			//PanelInputと組み合わせたコンストラクタ
			JudgedPanelInput(const PanelInput & panel_input, const Judge & judge)
				: PanelInput(panel_input), judge(judge) {}

			~JudgedPanelInput() {}
		}JudgedPanelInput;

	};
};


#endif