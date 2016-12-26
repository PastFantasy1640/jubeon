#pragma once

////////////////////////////////////////////////////
// (c) 2016  StreamBuffer.hpp  white
////////////////////////////////////////////////////

#ifndef JUBEON_PERSER_YOUBEATPARSER_HPP
#define JUBEON_PERSER_YOUBEATPARSER_HPP

#include <string>
#include <vector>

#include "Game/Sequence.hpp"

#include "Game/NoteDefinition.hpp"

namespace jubeon {
	namespace parser {
		class YoubeatParser : public jubeon::game::Sequence{
		public:
			YoubeatParser(const std::vector<std::string> youbeat_lines);
			
			static std::vector<std::string> loadFromFile(const std::string filename);
		
		private:

			class BpmColumn {
			public:
				BpmColumn(const unsigned int haku, const double bpm);


				const unsigned int haku;
				const double bpm;
				
			};

			typedef std::vector<BpmColumn> BpmTable;

			class Note_C{
			public:
				
				Note_C(const unsigned int haku, const unsigned int m, const unsigned int v, const jPanel p_no);
				

				const unsigned int haku;
				const unsigned int m;
				const unsigned int v;
				const jPanel p_no;
				
				game::Note convertToNote(const BpmTable bpm_table, const jMillisec offset) const;
			};

			std::vector<game::Note> parse(const std::vector<std::string> lines);
		
		};
	}
}

#endif