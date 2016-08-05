#include "PlayRecord.hpp"

#include <fstream>
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
	ofst << "date:" + this->date << std::endl;
	ofst << "name:" + this->name << std::endl;

	//���̏����o��
	std::string type_str;
	std::string judge_str;
	for (auto p = this->judged_list->begin(); p != this->judged_list->end(); p++) {
		switch (p->t) {
		case input::Type::PUSH: type_str = "PUSH"; break;
		case input::Type::RELEASE: type_str = "RELEASE"; break;
		}

		switch (p->judge) {
		case PERFECT:	judge_str = "PERFECT";
		case GREAT:		judge_str = "GREAT";
		case GOOD:		judge_str = "GOOD";
		case EARLY:		judge_str = "EARLY";
		case LATE:		judge_str = "LATE";
		case MISS:		judge_str = "MISS";
		case NOJUDGE:	judge_str = "NOJUDGE";
		}
		ofst << std::to_string(p->ms) << "," << std::to_string(p->panel_no) << "," << type_str << "," << judge_str << std::endl;
	}

	systems::Logger::information("�v���C�L�^�t�@�C���̕ۑ����������܂���");

	return true;
}

bool jubeon::game::PlayRecord::readFromFile(const std::string src)
{
	return false;
}

const std::shared_ptr<std::vector<jubeon::game::JudgedPanelInput>> jubeon::game::PlayRecord::getJudgedList() const
{
	return this->judged_list;
}

std::vector<jubeon::game::JudgedPanelInput>::const_iterator jubeon::game::PlayRecord::getIteratorFromTime(const std::vector<JudgedPanelInput>& list, const int ms)
{
	//�����_���g���Ă݂�H
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
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


