#include "PlayRecord.hpp"

#include <functional>

#include <iostream>



/*
jubeon::game::PlayRecord::PlayRecord()
{
	this->ck.restart();
}

jubeon::game::PlayRecord::~PlayRecord()
{
}

std::unique_ptr<std::list<jubeon::game::PanelInput>> jubeon::game::PlayRecord::getNoJudgedList(void)
{
	return std::move(this->no_judge_list);
}

void jubeon::game::PlayRecord::setJudgedList(NoJudgedList list)
{


	for (auto p : *list) {
		//�}�����
		//��Ԋy�Ȃ̂͌��ɒǉ�
		if (!this->judged_list.empty()) {
			//�󂶂�Ȃ�
			if ((--this->judged_list.end())->ms <= p.ms) {
				//��Ԍ��ɒǉ����[�I������[�I
				this->judged_list.push_back(p);
			}
			else {
				//�ǉ�
				this->judged_list.insert(this->getPanelInputFromTime(p.ms), p);
			}
		}
		else {
			//�󂾂����B
			//�Ƃɂ����ǉ�
			this->judged_list.push_back(p);
		}
	}

	//list�͂����Ŗ��s���Ă��炤


}
/*
void jubeon::game::PlayRecord::process(const unsigned char panel_no, const Type type)
{
	//�X���b�h�Z�[�t�ɍ��K�v������B
	//����no_judge_list�̃C���X�^���X�����邩�m�F
	std::lock_guard<std::mutex> lock(this->mtx);

	//�C���X�^���X�����邩
	if (!this->no_judge_list) {
		//�C���X�^���X����
		this->no_judge_list.reset(new std::list<jubeon::game::PanelInput>());
	}

	//�ǉ�
	jubeon::game::PanelInput pi;
	pi.ms = this->ck.getElapsedTime().asMilliseconds();
	pi.t = type;
	pi.panel_no = panel_no;
	pi.j = jubeon::game::Judge::NOJUDGE;

	this->no_judge_list->push_back(pi);
}*/
/*
unsigned int jubeon::game::PlayRecord::getTime() const
{
	return this->ck.getElapsedTime().asMicroseconds();
}

const jubeon::game::PanelInput * jubeon::game::PlayRecord::getJudgedInput(const size_t idx) const
{
	if(idx < this->judged_list.size())	return &this->judged_list[idx];
	return nullptr;
}

std::vector<jubeon::game::PanelInput>::const_iterator jubeon::game::PlayRecord::getPanelInputFromTime(const unsigned int ms) const
{
	//��낶��Ȃ��̂ŁA�񕪒T��
	//�����_���g���Ă݂�H
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
	{
		//�T���̍��E���w�肵�āA�Ō�ɑ}������C���f�b�N�X�̈ʒu��Ԃ�
		//�I������
		if (right == left) return right;
		
		if (right - 1 == left) {
			if (this->getJudgedInput(left)->ms <= ms) return right;
			else return left;
		}

		//�I�����Ȃ���
		//���Ȃ݂�right�͗̈��+1�̏ꏊ
		size_t center = (left + right) / 2;
		if (this->getJudgedInput(center)->ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, this->judged_list.size(), ms);

	if (idx > this->judged_list.size()) {
		//��������
		//�Ƃ肠�����G���[�o��
		std::cerr << "Error!!! PlayRecord.cpp Idx was invalid." << std::endl;
		return this->judged_list.end();
	}

	return this->judged_list.begin() + idx;
}

std::vector<jubeon::game::PanelInput>::const_iterator jubeon::game::PlayRecord::getPanelInputListEnd(void) const
{
	return this->judged_list.end();
}

std::vector<jubeon::game::PanelInput>::const_iterator jubeon::game::PlayRecord::getPanelInputListBegin(void) const
{
	return this->judged_list.begin();
}
*/