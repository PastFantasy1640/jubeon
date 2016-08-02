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

void jubeon::game::PlayRecord::addJudged(const jubeon::input::PanelInput & p, Judge & judge)
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
		//挿入作業
		//一番楽なのは後ろに追加
		if (!this->judged_list.empty()) {
			//空じゃない
			if ((--this->judged_list.end())->ms <= p.ms) {
				//一番後ろに追加だー！やったー！
				this->judged_list.push_back(p);
			}
			else {
				//追加
				this->judged_list.insert(this->getPanelInputFromTime(p.ms), p);
			}
		}
		else {
			//空だった。
			//とにかく追加
			this->judged_list.push_back(p);
		}
	}

	//listはここで命尽きてもらう


}
/*
void jubeon::game::PlayRecord::process(const unsigned char panel_no, const Type type)
{
	//スレッドセーフに作る必要がある。
	//あとno_judge_listのインスタンスがあるか確認
	std::lock_guard<std::mutex> lock(this->mtx);

	//インスタンスがあるか
	if (!this->no_judge_list) {
		//インスタンス生成
		this->no_judge_list.reset(new std::list<jubeon::game::PanelInput>());
	}

	//追加
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
	//後ろじゃないので、二分探索
	//ラムダ式使ってみる？
	std::function<size_t(size_t, size_t, unsigned int)> search = [&](size_t left, size_t right, unsigned int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;
		
		if (right - 1 == left) {
			if (this->getJudgedInput(left)->ms <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = (left + right) / 2;
		if (this->getJudgedInput(center)->ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, this->judged_list.size(), ms);

	if (idx > this->judged_list.size()) {
		//おかしい
		//とりあえずエラー出力
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
