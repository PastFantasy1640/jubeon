#pragma once

#ifndef JUBEON_GAME_JUDGEDPANELINPUT_HPP
#define JUBEON_GAME_JUDGEDPANELINPUT_HPP

#include "JudgeDefinition.hpp"
#include "Input/PanelInput.hpp"

namespace jubeon {
	namespace game {

		typedef struct JudgedPanelInput : jubeon::input::PanelInput {
		public:
			const Judge judge;	//�W���b�W��񂪒ǉ�

								//�S�w��R���X�g���N�^
			JudgedPanelInput(unsigned char panel_no, jubeon::Type t, unsigned int ms, const Judge & judge)
				: judge(judge), PanelInput(panel_no, t, ms) {}

			//PanelInput�Ƒg�ݍ��킹���R���X�g���N�^
			JudgedPanelInput(const PanelInput & panel_input, const Judge & judge)
				: PanelInput(panel_input), judge(judge) {}

			~JudgedPanelInput() {}
		}JudgedPanelInput;

	};
};


#endif