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

	jubeon::systems::Logger::information("[YoubeatParser]Start to parse. " + std::to_string(lines.size()) + "lines.");


	//BodySource
	std::vector<std::string> block;

	std::array<char,16> pos_str;
	std::vector<std::string> note_strv;

	std::vector<std::unique_ptr<Note_C>> note_c;

	std::vector<game::Note> result;

	unsigned int haku = 0;
	jMillisec offset = 0;

	//Prepare BPM Table
	BpmTable bpm_table;
	
	//Hold List
	std::list<Hold> hold_list;

	//parse block
	for (auto line = lines.begin(); line != lines.end(); line++) {

		if (line->empty()) continue;

		if (line->at(0) == '#') {
			//�R�}���h��
			double bpm;
			try {
				bpm = std::stod(line->substr(1));
				bpm_table.push_back(BpmColumn(haku, bpm));
				systems::Logger::information("[YoubeatParser]BPM Changed. BPM : " + std::to_string(bpm));
			}
			catch (const std::invalid_argument & e) {
				systems::Logger::warning("[YoubeatParser]Invalid BPM :" + *line);
			}
			
			continue;
		}
		else if (line->at(0) == '@') {
			//�I�t�Z�b�g
			try {
				if(offset == 0) offset = std::stoi(line->substr(1));
				systems::Logger::information("[YoubeatParser]Offset : " + std::to_string(offset) + "ms");
			}
			catch (const std::invalid_argument & e) {
				systems::Logger::warning("[YoubeatParser]Invalid Offset :" + *line);
			}
			continue;
		}
		else if (line->at(0) == '[') {
			//�z�[���h�̎w��
			//[�p�l���ԍ�:�o���p�l��,�I�[���ʕ�����]
			jPanel to, from;
			char pchar;

			//�p�[�X
			this->_holdParse(*line, &to, &from, &pchar);

			//�z�[���h���X�g�֒ǉ�
			hold_list.emplace_back(Hold(to, from, pchar));

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
			//char c : �^�C�~���O�ɂ�����ꕶ��
			//char p : �p�l���ԍ��ɂ�����ꕶ��
			for (std::string s : note_strv) {
				int m = 0;
				for (char c : s) {
					//�܂��z�[���h�̃`�F�b�N
					for (auto hold = hold_list.begin(); hold != hold_list.end(); hold++) {
						if (hold->end_charactor == c && !hold->emptyStart() && hold->emptyEnd()) {
							//End of Hold
							//const Note_C * ref = hold->getStart();
							//[TO DO] setEnd���������āA���Note_C����Note�փR���o�[�g����Ƃ���Duration���v�Z�ł���悤�ɂ���΂����B
							std::unique_ptr<Note_C> hold_end(new Note_C(haku, m, s.length(), hold->to, game::Note::HOLD_END));
							hold->setEnd(hold_end.get());
							note_c.emplace_back(std::move(hold_end));	//Add End
						}
					}

					if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
						jPanel t_pno = 0;
						for (char p : pos_str) {
							if (c == p) {
								//�z�[���h�J�n���H
								bool isHold = false;
								for (auto hold = hold_list.rbegin(); hold != hold_list.rend(); hold++) {
									if (hold->emptyStart() && hold->to == t_pno) {
										//�z�[���h�J�n
										std::unique_ptr<Note_C> hold_start(new Note_C(haku, m, s.length(), hold->to, hold->from));
										hold->setStart(hold_start.get());
										note_c.emplace_back(std::move(hold_start));
										isHold = true;
										break;
									}
								}
								if(!isHold) note_c.emplace_back(new Note_C(haku, m, s.length(),t_pno));
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

	
	//Hold convert
	for (auto hold = hold_list.begin(); hold != hold_list.end(); hold++) {
		if (!hold->emptyEnd() && !hold->emptyStart()) {
			hold->getStart()->setDuration(hold->getDuration(bpm_table));
		}
	}

	//���ʕϊ�
	for (auto nc = note_c.begin(); nc != note_c.end(); nc++) {
		result.push_back((*nc)->convertToNote(bpm_table, offset));
	}

	
	return result;
}

void jubeon::parser::YoubeatParser::_holdParse(const std::string & line, jPanel * pno, jPanel * appear_pno, char * c)
{
	bool err = false;
	//�z�[���h�̎w��
	//[�p�l���ԍ�:�o���p�l��,�I�[���ʕ�����]
	std::string pno_str, appear_str, end_str;
	std::string * ptr = &pno_str;
	for (auto p : line) {
		if (p == '[' || p == ']') continue;
		else if (p == ':') ptr = &appear_str;
		else if (p == ',') ptr = &end_str;
		else ptr->push_back(p);
	}

	//�\���G���[�`�F�b�N
	if (pno_str.empty()) {
		jubeon::systems::Logger::warning("Empty panel No. COMMAND LINE : " + line);
		err = true;
	}
	if (appear_str.empty()) {
		jubeon::systems::Logger::warning("Empty appearing panel No. COMMAND LINE : " + line);
		err = true;
	}
	if (end_str.empty()) {
		jubeon::systems::Logger::warning("Empty note charactor. COMMAND LINE : " + line);
		err = true;
	}
	if (err) return;

	//�^�ϊ�
	int pno_ret, ap_pno_ret;
	try {
		pno_ret = std::stoi(pno_str);
		ap_pno_ret = std::stoi(appear_str);
	}
	catch (std::invalid_argument e) {
		jubeon::systems::Logger::warning("Failed to cast to integer. COMMAND LINE : " + line);
		err = true;
	}
	if (err) return;

	//�͈̓`�F�b�N
	if (!(pno_ret >= 0 && pno_ret < 16)) {
		jubeon::systems::Logger::warning("Panel No. is out of bounds. COMMAND LINE : " + line);
		err = true;
	}
	if (!(ap_pno_ret >= 0 && ap_pno_ret < 16)) {
		jubeon::systems::Logger::warning("Panel No. is out of bounds. COMMAND LINE : " + line);
		err = true;
	}
	if (err) return;

	//���
	*pno = static_cast<jPanel>(pno_ret);
	*appear_pno = static_cast<jPanel>(ap_pno_ret);
	*c = end_str[0];

	jubeon::systems::Logger::information("[YoubeatParser]HOLD:panel No:" + pno_str + " ,appear panel No:" + appear_str + " ,end charactor:" + end_str.substr(0, 1));
}

	


