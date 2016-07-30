//author white
//INIFileReader class source

#include <vector>
#include <iostream>
#include <stdio.h>
#include "INIFileReader.hpp"

using namespace wg::systems;

wg::systems::INIFileReader::INIFileReader() : data(nullptr), filename(""), file_stream(nullptr), is_load_successfully(false){
	this->data = nullptr;
	this->filename = "";
	this->file_stream = nullptr;
	this->is_load_successfully = false;
}

wg::systems::INIFileReader::INIFileReader(const INIFileReader & copy) : INIFileReader()
{

	this->filename = copy.filename;
	this->is_load_successfully = copy.is_load_successfully;
	if (this->is_load_successfully == true){
		//もとにデータ実体があるか
		if (copy.data != nullptr) {
			//実体をコピー
			this->data = new std::vector<INIFileReader::INIFileReaderElements>;
			*(this->data) = *(copy.data);
		}
	}
}

wg::systems::INIFileReader::~INIFileReader(void) 
{
	this->clear();
}

bool wg::systems::INIFileReader::load(const std::string filename) {

	if (this->is_load_successfully) return false;

	this->filename = filename;

	//ファイルオープン
	this->file_stream = new std::fstream;
	this->data = new std::vector<INIFileReader::INIFileReaderElements>;
	//領域の確保に成功したか
	if (this->file_stream == nullptr) return false;

	this->file_stream->open(filename,std::ios::in);
	
	if (!this->file_stream || this->file_stream->fail()) {	//読み込み失敗
		delete this->file_stream;
		this->file_stream = nullptr;
		return false;
	}


	//行で読む
	std::string line;
	std::string section = "";

	while (true) {
		if (this->file_stream->eof() || this->file_stream->fail()) break;	//ファイルの最後
		std::getline(*this->file_stream, line);

		INIFileReaderElements tmp = this->_Psc(line);

		//データの走査終了
		//セクションでなければデータを登録
		if (tmp.section.length() > 0) {
			//セクション
			section = tmp.section;
		}
		else if(tmp.key.length() > 0){
			tmp.section = section;
			this->data->push_back(tmp);
		}
	}

	this->file_stream->close();
	delete this->file_stream;
	this->file_stream = nullptr;
	this->is_load_successfully = true;
	return true;
}

void wg::systems::INIFileReader::clear() {
	//もしファイルがロードしてたら削除する
	//file_streamは削除されているはず
	if (this->data != nullptr) {
		this->data->clear();
		delete this->data;
		this->data = nullptr;
	}

	if (this->file_stream != nullptr) {
		//ありえない
		this->file_stream->close();
		delete this->file_stream;
		this->file_stream = nullptr;
	}
	this->is_load_successfully = false;
}

bool wg::systems::INIFileReader::flush(void)
{
	if (!this->is_load_successfully) return false;
	this->clear();
	return this->load(this->filename);
}

wg::systems::INIFileReader::INIFileReaderElements wg::systems::INIFileReader::_Psc(const std::string s)
{

	//行で読む
	std::string line = s;
	std::string section = "";

	bool is_dq = false;	//ダブルクォート
	bool is_seq = false;	//セクション
	INIFileReaderElements tmp;
	std::string * p_str = &tmp.key;
	for (std::string::iterator c = line.begin(); c != line.end(); c++) {
		//1文字ずつ走査
		switch (*c) {
		case ' ':
			//スペースの時
			//ダブルクオート中でなければ読み飛ばす
			if (is_dq) {
				p_str->push_back(' ');
			}
			break;

		case '=':
			//イコールの場合
			//バリューに切り替え
			p_str = &tmp.value;
			break;

		case '\"':
			if (is_dq) is_dq = false;
			else is_dq = true;

		case ';':
			//コメント
			//次の行へ
			if (!is_dq) *c = 0;
			break;

		case '[':
			//ダブルクオートの中でなければセクション判定
			if (!is_dq) {
				is_seq = true;
				section = "";
			}
			else {
				p_str->push_back('[');
			}
			break;

		case ']':
			//ダブルクオートの中でなければセクション終了、読みとばす
			if (is_seq) *c = 0;
			else p_str->push_back(']');
			break;

		case '\n':
		case '\0':
			break;

		default:
			//その他文字列
			//どんどん追加
			if (is_seq) section.push_back(*c);
			else p_str->push_back(*c);
		}

		if (*c == 0) break;	//行終了
	}

	if(is_seq) tmp.section = section;

	return tmp;
}

bool wg::systems::INIFileReader::_ISp(const std::string s) const
{
	for (std::string::const_iterator c = s.begin(); c != s.end(); c++) {
		if (*c == ' ') return true;
	}
	return false;
}

std::string wg::systems::INIFileReader::get(const std::string section, const std::string key, const std::string def_str, bool * is_existed) const {
	if (is_existed != nullptr) *is_existed = false;

	if (this->is_load_successfully == false) {
		return def_str;
	}

	for (std::vector<INIFileReaderElements>::const_iterator p = this->data->begin(); p != this->data->end(); p++) {
		if (p->section.compare(section) == 0 && p->key.compare(key) == 0) {
			if (is_existed != nullptr) *is_existed = true;
			return p->value;
		}
	}
	
	return def_str;
}

bool wg::systems::INIFileReader::update(const std::string section, const std::string key, std::string value) {

	if (!this->is_load_successfully) return false;

	//空白が含まれるか
	if (this->_ISp(value)) {
		//含まれるので、始点終点をダブルクォーテーションで囲む
		value = "\"" + value + "\"";
	}

	this->file_stream = new std::fstream;
	if (this->file_stream == nullptr) return false;
	
	//ファイルオープン
	this->file_stream->open(this->filename, std::ios::in);
	if (!this->file_stream || this->file_stream->fail()) {	//読み込み失敗
		delete this->file_stream;
		this->file_stream = nullptr;
		return false;
	}

	std::string line;
	std::vector<std::string> lines;
	while (true) {
		if (this->file_stream->eof() || this->file_stream->fail()) break;
		std::getline(*this->file_stream, line);
		lines.push_back(line);
	}

	this->file_stream->close();

	this->file_stream->open(this->filename + "_", std::ios::out);
	if (!this->file_stream || this->file_stream->fail()) {	//読み込み失敗
		delete this->file_stream;
		return false;
	}

	//バックアップの作成
	for (std::vector<std::string>::const_iterator s = lines.begin(); s != lines.end();) {
		*this->file_stream << *s;
		s++;
		if (s != lines.end()) *this->file_stream << std::endl;
	}

	this->file_stream->close();
	if (!this->file_stream || this->file_stream->fail()) {	//失敗
		std::cerr << "INIFileReader.lib:failed to close file." << std::endl;
		delete this->file_stream;
		return false;
	}

	this->file_stream->open(this->filename, std::ios::out | std::ios::trunc);
	if (!this->file_stream || this->file_stream->fail()) {	//読み込み失敗
		delete this->file_stream;
		return false;
	}
	

	//行で読む
	std::string sec = "";
	INIFileReaderElements tmp;
	std::string * p_str = &tmp.key;
	bool sec_match = (section.compare("") == 0);	//セクションがマッチしている場合true
	bool exchanged = false;	//置換したか
	for (std::vector<std::string>::iterator line = lines.begin(); ;) {
		if (line == lines.end()) {
			//ファイルの最後だった
			if (!exchanged) {
				*this->file_stream << std::endl;
				if (sec_match) {
					*this->file_stream << key << " = " << value << std::endl;
				}
				else {
					//該当するセクションがなかった
					//追加
					*this->file_stream << "[" << section << "]" << std::endl;
					*this->file_stream << key << " = " << value << std::endl;
				}
			}
			//ループ終了

			break;
		}

		bool is_seq = false;

		tmp = this->_Psc(*line);

		//データの走査終了
		//セクションでなければデータを登録
		if (tmp.section.length() > 0) {
			//セクション
			sec = tmp.section;
			is_seq = true;
		}
		else if (tmp.key.length() > 0) {
			tmp.section = sec;
		}

		bool wr = true;
		//データの走査終了
		if (!exchanged) {
			//置換はまだ
			if (is_seq) {
				//セクション切り替え
				if (sec_match) {
					//マッチセクションだった
					//残念ながら該当キーは無し
					//よって追加
					*this->file_stream << key << " = " << value << std::endl;
					exchanged = true;	//置換完了
				}
				else {
					//特にマッチングセクションではない
					//次はマッチングセクションか
					if (sec.compare(section) == 0) sec_match = true;	//マッチセクションでした。出るかな？
				}
			}
			else {
				//値だった
				if (sec_match) {
					//マッチセクションだからワンチャンある
					if (tmp.key.compare(key) == 0 && tmp.section.compare(section) == 0) {
						//一致した。書き直し
						*this->file_stream << key << " = " << value;
						exchanged = true;
						wr = false;
					}
				}
			}
		}
		else {
			//置換終わってる
		}
		if(wr) *this->file_stream << *line;
		line++;
		if (line != lines.end()) {
			//最後の行以外改行する
			*this->file_stream << std::endl;
		}
	}

	this->file_stream->close();
	delete this->file_stream;
	this->file_stream = nullptr;

	//全て成功したので、バックアップはさよなら
	remove(std::string(this->filename + "_").c_str());

	return true;
}