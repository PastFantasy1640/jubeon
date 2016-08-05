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
			Judge judge;	//�W���b�W��񂪒ǉ�

			//�f�t�H���g�R���X�g���N�^
			JudgedPanelInput() {}

			//�S�w��R���X�g���N�^
			JudgedPanelInput(unsigned char panel_no, jubeon::input::Type t, unsigned int ms, const Judge & judge)
				: judge(judge), PanelInput(panel_no,t,ms) {}
			
			//PanelInput�Ƒg�ݍ��킹���R���X�g���N�^
			JudgedPanelInput(const PanelInput & panel_input, const Judge & judge)
				: PanelInput(panel_input), judge(judge) {}
		}JudgedPanelInput;

		class PlayRecord {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//����ς݂�ǉ�
			void addJudged(const jubeon::input::PanelInput p, Judge judge);
			void addJudged(const JudgedPanelInput judged_p);

			//�t�@�C���֏����o��(TO DO : ������)
			bool writeToFile(const std::string dst);

			//�t�@�C������ǂݏo��(TO DO : ������)
			bool readFromFile(const std::string src);
			
			//���X�g���Q�ƂƂ��Ď擾����
			const std::shared_ptr<std::vector<JudgedPanelInput>> getJudgedList() const;

			//�����֐�
			static std::vector<JudgedPanelInput>::const_iterator getIteratorFromTime(const std::vector<JudgedPanelInput> & list ,const int ms);

		private:
			
			
			//����ς݂̃��X�g
			std::shared_ptr<std::vector<JudgedPanelInput>> judged_list;

		};
	}
}

#endif