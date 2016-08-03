#include "PlayRecord.hpp"

//#include <functional>


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
	JudgedPanelInput tmp;
	tmp.ms = p.ms;
	tmp.panel_no = p.panel_no;
	tmp.t = p.t;
	tmp.judge = judge;

	//追加
	this->addJudged(tmp);
}

void jubeon::game::PlayRecord::addJudged(const JudgedPanelInput judged_p)
{
	//リストへ追加
	this->judged_list->push_back(judged_p);
}

bool jubeon::game::PlayRecord::writeToFile(const std::string dst)
{
	return false;
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
	//ラムダ式使ってみる？
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;

		if (right - 1 == left) {
			if (list[left].ms <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = (left + right) / 2;
		if (list[center].ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, list.size(), ms);

	if (idx > list.size()) {
		//おかしい
		//とりあえずエラー出力
		systems::Logger::warning("二分探索に失敗しています");
		return list.end();
	}

	return list.begin() + idx;
}


