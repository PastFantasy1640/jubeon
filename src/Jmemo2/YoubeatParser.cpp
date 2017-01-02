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
		std::cerr << "失敗" << std::endl;
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
			//コマンド列
			this->_bpm(*line, haku, &bpm_table);
			continue;
		}
		else if (line->at(0) == '@') {
			this->_offset(*line, &offset);
			continue;
		}
		else if (line->at(0) == '[') {
			//ホールドの指定
			//[パネル番号:出現パネル,終端識別文字列]
			this->_holdAdd(*line, &hold_list);
			continue;
		}else if (line->length() < 4) continue;
		
		//add block
		//●ブロック化
		block.push_back(*line);

		if (block.size() == 4) {

			//●分離
			this->_separatePos(block, &pos_str);

			//*** note_strv
			this->_separateTiming(block, &note_strv);

			//●譜面化
			//char c : タイミングにおける一文字
			//char p : パネル番号における一文字
			for (std::string s : note_strv) {
				int m = 0;
				for (char c : s) {
					//まずホールドのチェック
					this->_addHoldEnd(c, haku, m, s, &hold_list, &note_c);

					if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
						jPanel t_pno = 0;
						for (char p : pos_str) {
							if (c == p) {
								//ホールド開始か？
								bool isHold = this->_addHoldStart(c, haku, m, s, t_pno, &hold_list, &note_c);
								if(!isHold) note_c.emplace_back(new Note_C(haku, m, s.length(),t_pno));
							}
							t_pno++;
						}
					}
					m++;
				}
				haku++;	//拍をカウントアップ
			}


			block.clear();
		}
	}

	//ここまでで譜面の解析は終わってるはず

	
	//Hold convert
	this->_calcHoldDuration(bpm_table, &hold_list);

	//譜面変換
	this->_convert(bpm_table, note_c, offset, &result);

	systems::Logger::information("[YoubeatParser]Finished to parse. Notes num : " + std::to_string(result.size()));
	
	return result;
}

void jubeon::parser::YoubeatParser::_holdParse(const std::string & line, jPanel * pno, jPanel * appear_pno, char * c)
{
	bool err = false;
	//ホールドの指定
	//[パネル番号:出現パネル,終端識別文字列]
	std::string pno_str, appear_str, end_str;
	std::string * ptr = &pno_str;
	for (auto p : line) {
		if (p == '[' || p == ']') continue;
		else if (p == ':') ptr = &appear_str;
		else if (p == ',') ptr = &end_str;
		else ptr->push_back(p);
	}

	//構文エラーチェック
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

	//型変換
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

	//範囲チェック
	if (!(pno_ret >= 0 && pno_ret < 16)) {
		jubeon::systems::Logger::warning("Panel No. is out of bounds. COMMAND LINE : " + line);
		err = true;
	}
	if (!(ap_pno_ret >= 0 && ap_pno_ret < 16)) {
		jubeon::systems::Logger::warning("Panel No. is out of bounds. COMMAND LINE : " + line);
		err = true;
	}
	if (err) return;

	//代入
	*pno = static_cast<jPanel>(pno_ret);
	*appear_pno = static_cast<jPanel>(ap_pno_ret);
	*c = end_str[0];

	jubeon::systems::Logger::information("[YoubeatParser]HOLD:panel No:" + pno_str + " ,appear panel No:" + appear_str + " ,end charactor:" + end_str.substr(0, 1));
}

void jubeon::parser::YoubeatParser::_bpm(const std::string & line, const unsigned int haku, BpmTable * bpm_table)
{
	double bpm;
	try {
		bpm = std::stod(line.substr(1));
		bpm_table->push_back(BpmColumn(haku, bpm));
		systems::Logger::information("[YoubeatParser]BPM Changed. BPM : " + std::to_string(bpm));
	}
	catch (const std::invalid_argument & e) {
		systems::Logger::warning("[YoubeatParser]Invalid BPM :" + line);
	}
}

void jubeon::parser::YoubeatParser::_offset(const std::string & line, int * offset)
{
	//オフセット
	try {
		if (offset == 0) *offset = std::stoi(line.substr(1));
		systems::Logger::information("[YoubeatParser]Offset : " + std::to_string(*offset) + "ms");
	}
	catch (const std::invalid_argument & e) {
		systems::Logger::warning("[YoubeatParser]Invalid Offset :" + line);
	}
}

void jubeon::parser::YoubeatParser::_holdAdd(const std::string & line, std::list<Hold>* hold_list)
{
	jPanel to, from;
	char pchar;

	//パース
	this->_holdParse(line, &to, &from, &pchar);

	//ホールドリストへ追加
	hold_list->emplace_back(Hold(to, from, pchar));
}

void jubeon::parser::YoubeatParser::_separatePos(const std::vector<std::string>& block, std::array<char, 16>* pos_str)
{
	//*** pos_str
	int y = 0;
	pos_str->fill('x');
	for (auto s : block) {
		for (int i = 0; i < 4 && i < s.length(); i++) {
			(*pos_str)[i + y * 4] = s[i];
		}
		y++;
	}
}

void jubeon::parser::YoubeatParser::_separateTiming(const std::vector<std::string>& block, std::vector<std::string>* note_strv)
{
	note_strv->clear();
	for (auto s : block) {
		//TO DO : ブロックからchar[16]とvector<string>へパース
		//[4文字]|[次のパイプ文字まで]
		//閉じのパイプ文字が無くても良い。
		bool md = false;
		unsigned int v = 1;

		std::string tmp;
		for (char c : s) {
			if (c == '|' && md) break;	//終わり
			else if (c == '|') md = true;
			else if (c == '\r' || c == '\n' || c == '\0') break;
			else if (md) {
				tmp.push_back(c);
			}
		}
		if (md) note_strv->push_back(tmp);
	}
}

void jubeon::parser::YoubeatParser::_addHoldEnd(const char c, const unsigned int haku, const unsigned int m, const std::string s, std::list<Hold>* hold_list, std::vector<std::unique_ptr<Note_C>> * note_c)
{
	for (auto hold = hold_list->begin(); hold != hold_list->end(); hold++) {
		if (hold->end_charactor == c && !hold->emptyStart() && hold->emptyEnd()) {
			//End of Hold
			//const Note_C * ref = hold->getStart();
			//[TO DO] setEndを実装して、後のNote_CからNoteへコンバートするときにDurationを計算できるようにすればいい。
			std::unique_ptr<Note_C> hold_end(new Note_C(haku, m, s.length(), hold->to, game::Note::HOLD_END));
			hold->setEnd(hold_end.get());
			note_c->emplace_back(std::move(hold_end));	//Add End
		}
	}
}

bool jubeon::parser::YoubeatParser::_addHoldStart(const char c, const unsigned int haku, const unsigned int m, const std::string s, const jPanel t_pno, std::list<Hold>* hold_list, std::vector<std::unique_ptr<Note_C>>* note_c)
{
	bool isHold = false;
	for (auto hold = hold_list->rbegin(); hold != hold_list->rend(); hold++) {
		if (hold->emptyStart() && hold->to == t_pno) {
			//ホールド開始
			std::unique_ptr<Note_C> hold_start(new Note_C(haku, m, s.length(), hold->to, hold->from));
			hold->setStart(hold_start.get());
			note_c->emplace_back(std::move(hold_start));
			isHold = true;
			break;
		}
	}
	return isHold;
}

void jubeon::parser::YoubeatParser::_calcHoldDuration(const jubeon::parser::YoubeatParser::BpmTable & bpm_table, std::list<Hold>* hold_list)
{
	for (auto hold = hold_list->begin(); hold != hold_list->end(); hold++) {
		if (!hold->emptyEnd() && !hold->emptyStart()) {
			hold->getStart()->setDuration(hold->getDuration(bpm_table));
		}
	}
}

void jubeon::parser::YoubeatParser::_convert(const BpmTable & bpm_table, const std::vector<std::unique_ptr<Note_C>> & note_c, const jMillisec offset, std::vector<game::Note>* result)
{
	for (auto nc = note_c.begin(); nc != note_c.end(); nc++) {
		result->push_back((*nc)->convertToNote(bpm_table, offset));
	}
}

