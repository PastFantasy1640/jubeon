#include "MusicBar.hpp"

jubeon::game::MusicBar::MusicBar()
	: before_check_ms(0), sequence(nullptr)
{
}

void jubeon::game::MusicBar::init(const Sequence * sequence, const Music * music)
{
	//解析
	double length = static_cast<double>(music->getMusicLength());

	//分ける
	for (size_t i = 0; i < BAR_SIZE; i++) {
		Bar b;
		b.ms = static_cast<unsigned int>(i * length / BAR_SIZE);
		b.result = Bar::Result::NJDGE;
		this->at(i) = b;
	}

	//解析
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
		//巻き戻った
		
	}

	MusicBar::iterator ite(this->begin());
	std::advance(ite, std::distance<MusicBar::const_iterator>(ite, this->search(now)));
	if (ite-- == this->begin()) return;

	for (; ite != this->begin(); ) {
		MusicBar::const_iterator ite2 = ite--;

		if (ite->result != Bar::NJDGE) break;

		//解析
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

	//二分探索
	//ラムダ式
	std::function<size_t(size_t, size_t, int)> search = [&](size_t left, size_t right, int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).ms <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = left + (right - left) / 2;
		if (this->at(center).ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, this->size(), ms);

	if (idx > this->size()) {
		//おかしい
		//とりあえずエラー出力
		return this->end();
	}

	return this->begin() + idx;
}
