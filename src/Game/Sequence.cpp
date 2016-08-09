#include "Sequence.hpp"

//lambda
#include <functional>

//cerr
#include <iostream>

jubeon::game::Sequence::Sequence(const std::vector<Note> notes)
	: std::vector<Note>(notes)
{
}

const jubeon::game::Note & jubeon::game::Sequence::at(size_t idx) const
{
	return std::vector<Note>::at(idx);
}

std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::begin() const
{
	return std::vector<Note>::begin();
}

std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::end() const
{
	return std::vector<Note>::end();
}

std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::search(const int ms) const
{
	//�񕪒T��
	//�����_��
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, int ms)
	{
		//�T���̍��E���w�肵�āA�Ō�ɑ}������C���f�b�N�X�̈ʒu��Ԃ�
		//�I������
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).getJustTime() <= ms) return right;
			else return left;
		}

		//�I�����Ȃ���
		//���Ȃ݂�right�͗̈��+1�̏ꏊ
		size_t center = (left + right) / 2;
		if (this->at(center).getJustTime() <= ms) return search(center, right, ms);
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

std::size_t jubeon::game::Sequence::size() const
{
	return std::vector<Note>::size();
}

