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
	//二分探索
	//ラムダ式
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
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

void jubeon::game::Sequence::sort(std::vector<Note>* src)
{
	//再帰処理
	//作業用領域の確保
	std::vector<Note> working_space(*src);

	//処理
	Sequence::sort(src->begin(), src->end(), &working_space);
}

void jubeon::game::Sequence::sort(const std::vector<Note>::iterator & begin, const std::vector<Note>::iterator & end, std::vector<Note> * ws)
{
	
	if ((begin + 1) >= end) return;	//分割しきった結果1つならそのまま返す
	else if ((begin + 2) == end) {
		//大小比較
		if (begin->getJustTime() > (begin+1)->getJustTime()) {
			//入れ替えが発生
			Note tmp = *(begin + 1);
			*(begin + 1) = *begin;
			*begin = tmp;
		}
		return;
	}
	else {
		//3つ以上の要素
		//半分に分けて
		size_t distance = std::distance(begin, end) / 2;
		std::vector<Note>::iterator center = begin + distance;

		//再帰的にやり直し
		Sequence::sort(begin, center, ws);
		Sequence::sort(center, end, ws);

		//マージ処理
		//前半はそのままコピー
		std::vector<Note>::iterator pt = ws->begin();
		std::vector<Note>::iterator p;
		for (p = begin; p < center; p++, pt++) *pt = *p;
		
		//後半をひっくり返してコピー
		for (p = end - 1; center <= p; p--, pt++) *pt = *p;

		//比べながら追加
		//wsの頭はws->begin()、後ろはpt--
		pt--;
		std::vector<Note>::iterator begin2 = begin;
		for (p = ws->begin(); p <= pt;) {
			if (p->getJustTime() > pt->getJustTime()) {
				*begin2 = *pt;	//後ろが小さい
				pt--;
			}
			else {
				*begin2 = *p;	//前が小さい
				p++;
			}
			begin2++;	//次へ進める
		}

		//ソート終わり
	}
}

