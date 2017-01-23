#include "Sequence.hpp"

//lambda
#include <functional>

//cerr
#include <iostream>

//const jubeon::jPanel jubeon::game::Note::HOLD_END;

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
	//二分探索
	//ラムダ式
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).first.getJustTime() <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = left + (right - left) / 2;
		if (this->at(center).first.getJustTime() <= ms) return search(center, right, ms);
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





