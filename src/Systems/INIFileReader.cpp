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
		//���ƂɃf�[�^���̂����邩
		if (copy.data != nullptr) {
			//���̂��R�s�[
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

	//�t�@�C���I�[�v��
	this->file_stream = new std::fstream;
	this->data = new std::vector<INIFileReader::INIFileReaderElements>;
	//�̈�̊m�ۂɐ���������
	if (this->file_stream == nullptr) return false;

	this->file_stream->open(filename,std::ios::in);
	
	if (!this->file_stream || this->file_stream->fail()) {	//�ǂݍ��ݎ��s
		delete this->file_stream;
		this->file_stream = nullptr;
		return false;
	}


	//�s�œǂ�
	std::string line;
	std::string section = "";

	while (true) {
		if (this->file_stream->eof() || this->file_stream->fail()) break;	//�t�@�C���̍Ō�
		std::getline(*this->file_stream, line);

		INIFileReaderElements tmp = this->_Psc(line);

		//�f�[�^�̑����I��
		//�Z�N�V�����łȂ���΃f�[�^��o�^
		if (tmp.section.length() > 0) {
			//�Z�N�V����
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
	//�����t�@�C�������[�h���Ă���폜����
	//file_stream�͍폜����Ă���͂�
	if (this->data != nullptr) {
		this->data->clear();
		delete this->data;
		this->data = nullptr;
	}

	if (this->file_stream != nullptr) {
		//���肦�Ȃ�
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

	//�s�œǂ�
	std::string line = s;
	std::string section = "";

	bool is_dq = false;	//�_�u���N�H�[�g
	bool is_seq = false;	//�Z�N�V����
	INIFileReaderElements tmp;
	std::string * p_str = &tmp.key;
	for (std::string::iterator c = line.begin(); c != line.end(); c++) {
		//1����������
		switch (*c) {
		case ' ':
			//�X�y�[�X�̎�
			//�_�u���N�I�[�g���łȂ���Γǂݔ�΂�
			if (is_dq) {
				p_str->push_back(' ');
			}
			break;

		case '=':
			//�C�R�[���̏ꍇ
			//�o�����[�ɐ؂�ւ�
			p_str = &tmp.value;
			break;

		case '\"':
			if (is_dq) is_dq = false;
			else is_dq = true;

		case ';':
			//�R�����g
			//���̍s��
			if (!is_dq) *c = 0;
			break;

		case '[':
			//�_�u���N�I�[�g�̒��łȂ���΃Z�N�V��������
			if (!is_dq) {
				is_seq = true;
				section = "";
			}
			else {
				p_str->push_back('[');
			}
			break;

		case ']':
			//�_�u���N�I�[�g�̒��łȂ���΃Z�N�V�����I���A�ǂ݂Ƃ΂�
			if (is_seq) *c = 0;
			else p_str->push_back(']');
			break;

		case '\n':
		case '\0':
			break;

		default:
			//���̑�������
			//�ǂ�ǂ�ǉ�
			if (is_seq) section.push_back(*c);
			else p_str->push_back(*c);
		}

		if (*c == 0) break;	//�s�I��
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

	//�󔒂��܂܂�邩
	if (this->_ISp(value)) {
		//�܂܂��̂ŁA�n�_�I�_���_�u���N�H�[�e�[�V�����ň͂�
		value = "\"" + value + "\"";
	}

	this->file_stream = new std::fstream;
	if (this->file_stream == nullptr) return false;
	
	//�t�@�C���I�[�v��
	this->file_stream->open(this->filename, std::ios::in);
	if (!this->file_stream || this->file_stream->fail()) {	//�ǂݍ��ݎ��s
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
	if (!this->file_stream || this->file_stream->fail()) {	//�ǂݍ��ݎ��s
		delete this->file_stream;
		return false;
	}

	//�o�b�N�A�b�v�̍쐬
	for (std::vector<std::string>::const_iterator s = lines.begin(); s != lines.end();) {
		*this->file_stream << *s;
		s++;
		if (s != lines.end()) *this->file_stream << std::endl;
	}

	this->file_stream->close();
	if (!this->file_stream || this->file_stream->fail()) {	//���s
		std::cerr << "INIFileReader.lib:failed to close file." << std::endl;
		delete this->file_stream;
		return false;
	}

	this->file_stream->open(this->filename, std::ios::out | std::ios::trunc);
	if (!this->file_stream || this->file_stream->fail()) {	//�ǂݍ��ݎ��s
		delete this->file_stream;
		return false;
	}
	

	//�s�œǂ�
	std::string sec = "";
	INIFileReaderElements tmp;
	std::string * p_str = &tmp.key;
	bool sec_match = (section.compare("") == 0);	//�Z�N�V�������}�b�`���Ă���ꍇtrue
	bool exchanged = false;	//�u��������
	for (std::vector<std::string>::iterator line = lines.begin(); ;) {
		if (line == lines.end()) {
			//�t�@�C���̍Ōゾ����
			if (!exchanged) {
				*this->file_stream << std::endl;
				if (sec_match) {
					*this->file_stream << key << " = " << value << std::endl;
				}
				else {
					//�Y������Z�N�V�������Ȃ�����
					//�ǉ�
					*this->file_stream << "[" << section << "]" << std::endl;
					*this->file_stream << key << " = " << value << std::endl;
				}
			}
			//���[�v�I��

			break;
		}

		bool is_seq = false;

		tmp = this->_Psc(*line);

		//�f�[�^�̑����I��
		//�Z�N�V�����łȂ���΃f�[�^��o�^
		if (tmp.section.length() > 0) {
			//�Z�N�V����
			sec = tmp.section;
			is_seq = true;
		}
		else if (tmp.key.length() > 0) {
			tmp.section = sec;
		}

		bool wr = true;
		//�f�[�^�̑����I��
		if (!exchanged) {
			//�u���͂܂�
			if (is_seq) {
				//�Z�N�V�����؂�ւ�
				if (sec_match) {
					//�}�b�`�Z�N�V����������
					//�c�O�Ȃ���Y���L�[�͖���
					//����Ēǉ�
					*this->file_stream << key << " = " << value << std::endl;
					exchanged = true;	//�u������
				}
				else {
					//���Ƀ}�b�`���O�Z�N�V�����ł͂Ȃ�
					//���̓}�b�`���O�Z�N�V������
					if (sec.compare(section) == 0) sec_match = true;	//�}�b�`�Z�N�V�����ł����B�o�邩�ȁH
				}
			}
			else {
				//�l������
				if (sec_match) {
					//�}�b�`�Z�N�V���������烏���`��������
					if (tmp.key.compare(key) == 0 && tmp.section.compare(section) == 0) {
						//��v�����B��������
						*this->file_stream << key << " = " << value;
						exchanged = true;
						wr = false;
					}
				}
			}
		}
		else {
			//�u���I����Ă�
		}
		if(wr) *this->file_stream << *line;
		line++;
		if (line != lines.end()) {
			//�Ō�̍s�ȊO���s����
			*this->file_stream << std::endl;
		}
	}

	this->file_stream->close();
	delete this->file_stream;
	this->file_stream = nullptr;

	//�S�Đ��������̂ŁA�o�b�N�A�b�v�͂���Ȃ�
	remove(std::string(this->filename + "_").c_str());

	return true;
}