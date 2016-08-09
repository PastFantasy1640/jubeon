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
	//二分探索
	//ラムダ式
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left).getJustTime() <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = (left + right) / 2;
		if (this->at(center).getJustTime() <= ms) return search(center, right, ms);
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

std::size_t jubeon::game::Sequence::size() const
{
	return std::vector<Note>::size();
}

