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
			JudgedPanelInput() {}
			JudgedPanelInput(unsigned char panel_no, jubeon::input::Type t, unsigned int ms, Judge judge)
				: judge(judge), PanelInput(panel_no,t,ms) {}
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