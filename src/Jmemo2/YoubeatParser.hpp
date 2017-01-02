#pragma once

////////////////////////////////////////////////////
// (c) 2016  StreamBuffer.hpp  white
////////////////////////////////////////////////////

#ifndef JUBEON_PERSER_YOUBEATPARSER_HPP
#define JUBEON_PERSER_YOUBEATPARSER_HPP

#include <string>
#include <vector>
#include <list>
#include <memory>

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
				Note_C(const unsigned int haku, const unsigned int m, const unsigned int v, const jPanel p_no, const jPanel from);
				Note_C(const Note_C & cp);

				const unsigned int haku;
				const unsigned int m;
				const unsigned int v;
				const jPanel p_no;
				const jPanel from_pno;
				
				game::Note convertToNote(const BpmTable & bpm_table, const jMillisec offset) const;

				void setDuration(unsigned int duration);
				unsigned int getDuration(void) const;
			private:
				unsigned int duration;
			};

			class Hold {
			public:
				Hold(const jPanel to, const jPanel from, const char endc);
				Hold(const Hold & copy);

				const jPanel to, from;
				const char end_charactor;

				unsigned int getDuration(const BpmTable & bpm_table) const;

				const Note_C * getStart() const;
				Note_C * getStart();
				bool emptyStart() const;
				const Note_C * getEnd() const;
				bool emptyEnd() const;
				void setStart(Note_C *const start);
				void setEnd(Note_C *const end);

			private:
				Hold();
				jMillisec duration;
				
				Note_C * start;
				Note_C * end;
			};

			std::vector<game::Note> parse(const std::vector<std::string> lines);

			void _holdParse(const std::string & line, jPanel * pno, jPanel * appear_pno, char * c);
			void _bpm(const std::string & line, const unsigned int haku, BpmTable * bpm_table);
			void _offset(const std::string & line, int * offset);
			void _holdAdd(const std::string & line, std::list<Hold> * hold_list);
			void _separatePos(const std::vector<std::string> & block, std::array<char, 16> * pos_str);
			void _separateTiming(const std::vector<std::string> & block, std::vector<std::string> * note_strv);
			void _addHoldEnd(const char c, const unsigned int haku, const unsigned int m, const std::string s, std::list<Hold> * hold_list, std::vector<std::unique_ptr<Note_C>> * note_c);
			bool _addHoldStart(const char c, const unsigned int haku, const unsigned int m, const std::string s, const jPanel t_pno, std::list<Hold> * hold_list, std::vector<std::unique_ptr<Note_C>> * note_c);
			void _calcHoldDuration(const BpmTable & bpm_table, std::list<Hold> * hold_list);
			void _convert(const BpmTable & bpm_table, const std::vector<std::unique_ptr<Note_C>> & note_c, const jMillisec offset, std::vector<game::Note> * result);
		};
	}
}

#endif