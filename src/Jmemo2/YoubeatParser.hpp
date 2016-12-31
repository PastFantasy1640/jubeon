#pragma once

////////////////////////////////////////////////////
// (c) 2016  StreamBuffer.hpp  white
////////////////////////////////////////////////////

#ifndef JUBEON_PERSER_YOUBEATPARSER_HPP
#define JUBEON_PERSER_YOUBEATPARSER_HPP

#include <string>
#include <vector>
#include <list>

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

			class Hold {
			public:
				Hold(const jPanel to, const jPanel from, const char endc);
				Hold(const Hold & copy);

				const jPanel to, from;
				const char end_charactor;
			private:
				Hold();
			};

			std::vector<game::Note> parse(const std::vector<std::string> lines);

			void _holdParse(const std::string & line, jPanel * pno, jPanel * appear_pno, char * c);
		
		};
	}
}

#endif