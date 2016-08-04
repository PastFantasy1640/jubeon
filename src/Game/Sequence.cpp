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

const std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::begin() const
{
	return std::vector<Note>::begin();
}

const std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::end() const
{
	return std::vector<Note>::end();
}

const std::vector<jubeon::game::Note>::const_iterator jubeon::game::Sequence::search(const int ms) const
{
	//�񕪒T��
	//�����_��
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
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

void jubeon::game::Sequence::sort(std::vector<Note>* src)
{
	//�ċA����
	//��Ɨp�̈�̊m��
	std::vector<Note> working_space(*src);

	//����
	Sequence::sort(src->begin(), src->end(), &working_space);
}

void jubeon::game::Sequence::sort(const std::vector<Note>::iterator & begin, const std::vector<Note>::iterator & end, std::vector<Note> * ws)
{
	
	if ((begin + 1) >= end) return;	//����������������1�Ȃ炻�̂܂ܕԂ�
	else if ((begin + 2) == end) {
		//�召��r
		if (begin->getJustTime() > (begin+1)->getJustTime()) {
			//����ւ�������
			Note tmp = *(begin + 1);
			*(begin + 1) = *begin;
			*begin = tmp;
		}
		return;
	}
	else {
		//3�ȏ�̗v�f
		//�����ɕ�����
		size_t distance = std::distance(begin, end) / 2;
		std::vector<Note>::iterator center = begin + distance;

		//�ċA�I�ɂ�蒼��
		Sequence::sort(begin, center, ws);
		Sequence::sort(center, end, ws);

		//�}�[�W����
		//�O���͂��̂܂܃R�s�[
		std::vector<Note>::iterator pt = ws->begin();
		std::vector<Note>::iterator p;
		for (p = begin; p < center; p++, pt++) *pt = *p;
		
		//�㔼���Ђ�����Ԃ��ăR�s�[
		for (p = end - 1; center <= p; p--, pt++) *pt = *p;

		//��ׂȂ���ǉ�
		//ws�̓���ws->begin()�A����pt--
		pt--;
		std::vector<Note>::iterator begin2 = begin;
		for (p = ws->begin(); p <= pt;) {
			if (p->getJustTime() > pt->getJustTime()) {
				*begin2 = *pt;	//��낪������
				pt--;
			}
			else {
				*begin2 = *p;	//�O��������
				p++;
			}
			begin2++;	//���֐i�߂�
		}

		//�\�[�g�I���
	}
}

