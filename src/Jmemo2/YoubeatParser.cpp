#include "YoubeatParser.hpp"

#include <fstream>
#include <iostream>
#include <array>
#include <stdexcept>

#include "Systems/Logger.hpp"

jubeon::parser::YoubeatParser::YoubeatParser(const std::vector<std::string> youbeat_lines)
	: Sequence(this->parse(youbeat_lines))
{
}


std::vector<std::string> jubeon::parser::YoubeatParser::loadFromFile(const std::string filename)
{
	std::vector<std::string> res;

	std::ifstream ifs(filename);
	std::string str;

	if (ifs.fail())
	{
		std::cerr << "���s" << std::endl;
		return res;
	}

	while (getline(ifs, str))	res.push_back(str);

	return res;
}

std::vector<jubeon::game::Note> jubeon::parser::YoubeatParser::parse(const std::vector<std::string> lines)
{

	//BodySource
	std::vector<std::string> block;

	std::array<char,16> pos_str;
	std::vector<std::string> note_strv;

	std::vector<Note_C> note_c;

	std::vector<game::Note> result;

	unsigned int haku = 0;
	jMillisec offset = 0;

	//Prepare BPM Table
	BpmTable bpm_table;
	
	

	//parse block
	for (auto line = lines.begin(); line != lines.end(); line++) {

		if (line->empty()) continue;

		if (line->at(0) == '#') {
			//�R�}���h��

			double bpm;
			try {
				bpm = std::stod(line->substr(1));
				bpm_table.push_back(BpmColumn(haku, bpm));
			}
			catch (const std::invalid_argument & e) {
				systems::Logger::warning("Invalid BPM :" + *line);
			}


			continue;
		}
		else if (line->at(0) == '@') {
			//�I�t�Z�b�g

			try {
				if(offset == 0) offset = std::stoi(line->substr(1));
			}
			catch (const std::invalid_argument & e) {
				systems::Logger::warning("Invalid Offset :" + *line);
			}


			continue;
		}
		else if (line->at(0) == '[') {
			continue;
		}

		if (line->length() < 4) continue;
		
		//add block
		//���u���b�N��
		block.push_back(*line);

		if (block.size() == 4) {

			//������

			//*** pos_str
			int y = 0;
			pos_str.fill('x');
			for (auto s : block) {
				for (int i = 0; i < 4 && i < s.length(); i++) {
					pos_str[i+y*4] = s[i];
				}
				y++;
			}

			//*** note_strv
			note_strv.clear();
			for (auto s : block) {
				//TO DO : �u���b�N����char[16]��vector<string>�փp�[�X
				//[4����]|[���̃p�C�v�����܂�]
				//���̃p�C�v�����������Ă��ǂ��B
				bool md = false;
				unsigned int v = 1;

				std::string tmp;
				for (char c : s) {
					if (c == '|' && md) break;	//�I���
					else if (c == '|') md = true;
					else if (c == '\r' || c == '\n' || c == '\0') break;
					else if (md) {
						tmp.push_back(c);
					}
				}
				if(md) note_strv.push_back(tmp);
			}

			//�����ʉ�
			for (std::string s : note_strv) {
				int m = 0;
				for (char c : s) {
					if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
						jPanel t_pno = 0;
						for (char p : pos_str) {
							if (c == p) {
								note_c.push_back(Note_C(haku, m, s.length(),t_pno));
							}
							t_pno++;
						}
					}
					m++;
				}
				haku++;	//�����J�E���g�A�b�v
			}


			block.clear();
		}

	}

	//�����܂łŕ��ʂ̉�͂͏I����Ă�͂�

	//���ʕϊ�
	for (auto nc : note_c) {
		result.push_back(nc.convertToNote(bpm_table, offset));
	}
	
	return result;
}

jubeon::parser::YoubeatParser::BpmColumn::BpmColumn(const unsigned int haku, const double bpm)
	: haku(haku), bpm(bpm)
{
}




jubeon::parser::YoubeatParser::Note_C::Note_C(const unsigned int haku, const unsigned int m, const unsigned int v, const jubeon::jPanel p_no)
	: haku(haku), m(m), v(v),p_no(p_no)
{
}

jubeon::game::Note jubeon::parser::YoubeatParser::Note_C::convertToNote(const BpmTable bpm_table, const jMillisec offset) const
{
	BpmTable::const_iterator p = bpm_table.begin();

	for (; p != bpm_table.end(); p++) {
		if (p->haku > this->haku) break;
	}

	double paramA = 0.0f;
	double paramB = 0.0f;
	double ms = 0.0f;

	// != p �܂łƂ��Čv�Z����΂���
	for (BpmTable::const_iterator cur = bpm_table.begin(); cur != p; cur++) {
		ms = paramA * cur->haku + paramB;
		
		paramA = 60000.0f / cur->bpm;
		paramB = ms - paramA * cur->haku;
	}

	//ms = paramA * (haku + m / v) + paramB
	return jubeon::game::Note(paramA * (static_cast<double>(this->haku) + static_cast<double>(this->m) / static_cast<double>(this->v)) + paramB + offset, this->p_no);

}
