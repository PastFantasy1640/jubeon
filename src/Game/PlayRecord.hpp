#pragma once

#ifndef jubeon_GAME_PLAYRECORD_HPP
#define jubeon_GAME_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

#include "JudgedPanelInput.hpp"
#include "Game/TypeDefinition.hpp"

#include "Sequence.hpp"

#include "Score.hpp"

#include "Music.hpp"

namespace jubeon {
	namespace game {

		typedef std::vector<std::unique_ptr<JudgedPanelInput>> JudgedPanelInputs;

		class PlayRecord : protected JudgedPanelInputs {
		public:

			PlayRecord(Sequence * sequence);
			virtual ~PlayRecord();

			//Judge
			//�����Œǉ�
			void judge(const input::PanelInput panel_input);

			void update(const Music * music);


			//�t�@�C���֏����o��(TO DO : ������)
			bool writeToFile(const std::string dst) const;

			//�t�@�C������ǂݏo��(TO DO : ������)
			bool readFromFile(const std::string src);
			
			void setPanelInputs(const std::vector<input::PanelInput> & pinputs);
			
			//�����֐�
			JudgedPanelInputs::const_iterator getIteratorFromTime(const int ms) const;

			const Score * getScore() const;

			using JudgedPanelInputs::const_iterator;
			using JudgedPanelInputs::begin;
			using JudgedPanelInputs::end;
			using JudgedPanelInputs::size;
			using JudgedPanelInputs::at;
			using JudgedPanelInputs::empty;
			using JudgedPanelInputs::operator[];

		private:

			PlayRecord();

			Sequence * sequence;
			
			std::string name;
			std::string date;
			
			Score score;

			std::list<input::PanelInput> pinputs;

		};
	}
}

#endif