#include "MusicBar.hpp"

jubeon::game::MusicBar::MusicBar()
	: before_check_ms(0), sequence(nullptr)
{
}

void jubeon::game::MusicBar::init(const Sequence * sequence, const Music * music)
{
	//���
	double length = static_cast<double>(music->getMusicLength());

	//������
	for (size_t i = 0; i < BAR_SIZE; i++) {
		Bar b;
		b.ms = static_cast<unsigned int>(i * length / BAR_SIZE);
		b.result = Bar::Result::NJDGE;
		this->at(i) = b;
	}

	//���
	Sequence::const_iterator ite = sequence->begin();
	for (size_t i = 0; i < BAR_SIZE; i++) {
		Sequence::const_iterator end;
		if (i == BAR_SIZE) end = sequence->end();
		else end = sequence->search(this->at(i + 1).ms);
		for (; ite != end && this->at(i).num < 8; ite++) {
			++this->at(i).num;
		}
		ite = end;
	}
}

void jubeon::game::MusicBar::update(const Music * music)
{
	unsigned int now = music->getPlayingCurrentTime();

	if (this->before_check_ms > now) {
		//�����߂���
		
	}

	MusicBar::iterator ite(this->begin());
	std::advance(ite, std::distance<MusicBar::const_iterator>(ite, this->search(now)));
	if (ite-- == this->begin()) return;

	for (; ite != this->begin(); ) {
		MusicBar::const_iterator ite2 = ite--;

		if (ite->result != Bar::NJDGE) break;

		//���
		Sequence::const_iterator seq_ite = this->sequence->search(ite->ms);
		ite->result = Bar::YELLOW;
		for (; seq_ite != this->sequence->end() && ite->result != Bar::GRAY; seq_ite++) {
			if (seq_ite->first.getJustTime() >= ite2->ms) break;

			if (seq_ite->second == nullptr) ite->result = Bar::GRAY;
			else if (seq_ite->second->judge == Judge::PERFECT) continue;
			else if (seq_ite->second->judge == Judge::GREAT ||
				seq_ite->second->judge == Judge::GOOD) ite->result = Bar::BLUE;
			else ite->result = Bar::GRAY;
		}
	
	}
	

}

std::array<jubeon::game::Bar, jubeon::game::BAR_SIZE>::const_iterator jubeon::game::MusicBar::search(const int ms)
{

	//�񕪒T��
	//�����_��
	std::function<size_t(size_t, size_t, int)> search = [&](size_t left, size_t right, int ms)
	{
		//�T���̍��E���w�肵�āA�Ō�ɑ}������C���f�b�N�X�̈ʒu��Ԃ�
		//�I������
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).ms <= ms) return right;
			else return left;
		}

		//�I�����Ȃ���
		//���Ȃ݂�right�͗̈��+1�̏ꏊ
		size_t center = left + (right - left) / 2;
		if (this->at(center).ms <= ms) return search(center, right, ms);
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
