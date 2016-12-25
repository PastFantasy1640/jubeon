#include "Sequence.hpp"

//lambda
#include <functional>

//cerr
#include <iostream>

jubeon::game::Sequence::Sequence(const Sequence & cp) 
	: Notes(cp)
{
}

jubeon::game::Sequence::Sequence(const std::vector<Note> notes)
{
	for (const Note n : notes) {
		this->emplace_back(NoteJudgePair(n, nullptr));
	}
}

void jubeon::game::Sequence::setJudgedPanelInput(const Notes::const_iterator target, JudgedPanelInput * judged)
{
	Notes::iterator ite(this->begin());

	std::advance(ite, std::distance<Notes::const_iterator>(ite, target));

	if (ite != this->end() && judged != nullptr) {
		ite->second = judged;
	}
}


jubeon::game::Notes::const_iterator jubeon::game::Sequence::search(const jubeon::jMillisec ms) const
{
	//�񕪒T��
	//�����_��
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, int ms)
	{
		//�T���̍��E���w�肵�āA�Ō�ɑ}������C���f�b�N�X�̈ʒu��Ԃ�
		//�I������
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).first.getJustTime() <= ms) return right;
			else return left;
		}

		//�I�����Ȃ���
		//���Ȃ݂�right�͗̈��+1�̏ꏊ
		size_t center = (left + right) / 2;
		if (this->at(center).first.getJustTime() <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, this->size(), ms);

	if (idx > this->size()) {
		//��������
		//�Ƃ肠�����G���[�o��
		return this->end();
	}

	return this->begin() + idx;
	
}



