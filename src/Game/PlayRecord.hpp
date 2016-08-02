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
			Judge judge;	//�W���b�W��񂪒ǉ�
		}JudgedPanelInput;

		class PlayRecord {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//����ς݂�ǉ�
			void addJudged(const jubeon::input::PanelInput & p, Judge & judge);
			void addJudged(const JudgedPanelInput & judged_p);

			//�t�@�C���֏����o��
			bool writeToFile(const std::string dst);

			//�t�@�C������ǂݏo��
			bool readFromFile(const std::string src);
			
			//judgedlist[idx]�̎擾
			const JudgedPanelInput & getJudgedInput(const size_t idx) const;

			//judgedlist�̎w�肳�ꂽms���x���A����ԋ߂����̂�const_iterator��Ԃ�
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputFromTime(const unsigned int ms) const;

			//judgedlist�̏I���C�e���[�^
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputListEnd(void) const;

			//judgedlist�̊J�n�C�e���[�^
			std::vector<JudgedPanelInput>::const_iterator & getPanelInputListBegin(void) const;

		private:
			
			
			//����ς݂̃��X�g
			std::vector <JudgedPanelInput> judged_list;

		};
	}
}

#endif