#include "PlayRecord.hpp"

#include <fstream>
#include <sstream>   // istringstream

#include "../Systems/Logger.hpp"


jubeon::game::PlayRecord::PlayRecord()
	: judged_list(new std::vector<JudgedPanelInput>())
{
}

jubeon::game::PlayRecord::~PlayRecord()
{
}

void jubeon::game::PlayRecord::addJudged(const jubeon::input::PanelInput p, Judge judge)
{
	//�ǉ�
	this->addJudged(JudgedPanelInput(p, judge));
}

void jubeon::game::PlayRecord::addJudged(const JudgedPanelInput judged_p)
{
	//���X�g�֒ǉ�
	this->judged_list->push_back(judged_p);
}

bool jubeon::game::PlayRecord::writeToFile(const std::string dst)
{
	//�����o��
	//����->ASCII
	//date:"20xx-xx-xx xx:xx:xx"
	//name:"wHite"
	//[ms],[panel],[type],[judge]
	//�Ȍ�EOF�܂�

	systems::Logger::information("�v���C�L�^�t�@�C���̕ۑ����J�n���܂��B");

	//�t�@�C���X�g���[��
	std::ofstream ofst(dst, std::ios::trunc);

	if (!ofst) {
		systems::Logger::warning("�v���C�L�^�t�@�C��" + dst + "���쐬�ł��܂���ł����B�L�^�͒��~����܂��B");
		return false;
	}

	//�w�b�_�̒ǉ�
	ofst << "date:" << this->date << std::endl;
	ofst << "name:" << this->name << std::endl;
	
	//���̏����o��
	std::string type_str;
	std::string judge_str;
	for (auto p = this->judged_list->begin(); p != this->judged_list->end(); p++) {
		switch (p->t) {
		case Type::PUSH: type_str = "PUSH"; break;
		case Type::RELEASE: type_str = "RELEASE"; break;
		}

		switch (p->judge) {
		case PERFECT:	judge_str = "PERFECT"; break;
		case GREAT:		judge_str = "GREAT";   break;
		case GOOD:		judge_str = "GOOD";	   break;
		case EARLY:		judge_str = "EARLY";   break;
		case LATE:		judge_str = "LATE";	   break;
		case MISS:		judge_str = "MISS";	   break;
		case NOJUDGE:	judge_str = "NOJUDGE"; break;
		}
		ofst << std::to_string(p->ms) << "," << std::to_string(p->panel_no) << "," << type_str << "," << judge_str << std::endl;
	}

	systems::Logger::information("�v���C�L�^�t�@�C���̕ۑ����������܂���");

	return true;
}

bool jubeon::game::PlayRecord::readFromFile(const std::string src)
{
	systems::Logger::information("�v���C�L�^�t�@�C���̓ǂݍ��݂��J�n���܂��B");

	//�܂�������list���폜
	this->judged_list->clear();

	//�t�@�C���X�g���[��
	std::ifstream ifst(src);

	if (!ifst || ifst.fail()) {
		systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "��ǂݍ��߂܂���ł����B");
		return false;
	}

	//�w�b�_�̓ǂݍ���
	//�f�[�^�̊ԈႢ������Α��I��
	std::string str;
	std::string str2;
	JudgedPanelInput tmp;

	//date��ǂݍ���
	std::getline(ifst, str);
	if (!str.substr(0, 5).compare("date:") == 0) {
		systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: date������܂���");
		return false;
	}
	this->date = str;

	//name��ǂݍ���
	std::getline(ifst, str);
	if (!str.substr(0, 5).compare("name:") == 0) {
		systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: name������܂���");
		return false;
	}
	this->name = str;

	//�I���܂Ń��[�v
	std::vector<std::string> tmp_vector;
	while (!ifst.eof())
	{
		// read by line
		std::getline(ifst, str);

		if (str.compare("") == 0) continue;

		//spilt
		const char delimiter = ',';
		std::istringstream line_separater(str);
		tmp_vector.clear();

		while (std::getline(line_separater, str2, delimiter)) {
			tmp_vector.push_back(str2);
		}

		//��������
		if (tmp_vector.size() != 4) {
			systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: �v�f�����ُ�ł��B");
			return false;
		}

		//����
		try {
			tmp.ms = std::stoi(tmp_vector[0]);
			tmp.panel_no = std::stoi(tmp_vector[1]);
		}
		catch (std::invalid_argument e) {
			systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: ���l�ɕϊ��ł��܂���");
			return false;
		}

		//�^�C�v
		if (tmp_vector[2].compare("PUSH") == 0) tmp.t = PUSH;
		else if (tmp_vector[2].compare("RELEASE") == 0) tmp.t = RELEASE;
		else {
			systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: PUSH�ARELEASE�ȊO�̒l���w�肳��Ă��܂�");
			return false;
		}

		//����
		if (tmp_vector[3].compare("PERFECT") == 0) tmp.judge = PERFECT;
		else if (tmp_vector[3].compare("GREAT") == 0) tmp.judge = GREAT;
		else if (tmp_vector[3].compare("GOOD") == 0) tmp.judge = GOOD;
		else if (tmp_vector[3].compare("EARLY") == 0) tmp.judge = EARLY;
		else if (tmp_vector[3].compare("LATE") == 0) tmp.judge = LATE;
		else if (tmp_vector[3].compare("MISS") == 0) tmp.judge = MISS;
		else if (tmp_vector[3].compare("NOJUDGE") == 0) tmp.judge = NOJUDGE;
		else {
			systems::Logger::warning("�v���C�L�^�t�@�C��" + src + "�̕��@�ɊԈႢ������܂��B: ����̒l���ُ�ł�");
			return false;
		}

		this->judged_list->push_back(tmp);
	}

	systems::Logger::information("�v���C�L�^�t�@�C���̓ǂݍ��݂��������܂���");

	return true;
}

const std::shared_ptr<std::vector<jubeon::game::JudgedPanelInput>> jubeon::game::PlayRecord::getJudgedList() const
{
	return this->judged_list;
}

std::vector<jubeon::game::JudgedPanelInput>::const_iterator jubeon::game::PlayRecord::getIteratorFromTime(const std::vector<JudgedPanelInput>& list, const int ms)
{
	//�����_���g���Ă݂�H
	std::function<size_t(size_t, size_t, int)> search = [&](size_t left, size_t right, int ms)
	{
		//�T���̍��E���w�肵�āA�Ō�ɑ}������C���f�b�N�X�̈ʒu��Ԃ�
		//�I������
		if (right == left) return right;

		if (right - 1 == left) {
			if (list[left].ms <= ms) return right;
			else return left;
		}

		//�I�����Ȃ���
		//���Ȃ݂�right�͗̈��+1�̏ꏊ
		size_t center = (left + right) / 2;
		if (list[center].ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, list.size(), ms);

	if (idx > list.size()) {
		//��������
		//�Ƃ肠�����G���[�o��
		systems::Logger::warning("�񕪒T���Ɏ��s���Ă��܂�");
		return list.end();
	}

	return list.begin() + idx;
}


