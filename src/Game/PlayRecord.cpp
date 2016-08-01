#include "PlayRecord.hpp"

#include <functional>

#include <iostream>

jubeat_online::game::PlayRecord::PlayRecord()
{
	this->ck.restart();
}

jubeat_online::game::PlayRecord::~PlayRecord()
{
}

std::unique_ptr<std::list<jubeat_online::game::PlayRecord::PanelInput>> jubeat_online::game::PlayRecord::getNoJudgedList(void)
{
	return std::move(this->no_judge_list);
}

void jubeat_online::game::PlayRecord::setJudgedList(NoJudgedList list)
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

void jubeat_online::game::PlayRecord::process(const unsigned char panel_no, const Type type)
{
	//スレッドセーフに作る必要がある。
	//あとno_judge_listのインスタンスがあるか確認
	std::lock_guard<std::mutex> lock(this->mtx);

	//インスタンスがあるか
	if (!this->no_judge_list) {
		//インスタンス生成
		this->no_judge_list.reset(new std::list<PanelInput>());
	}

	//追加
	PanelInput pi;
	pi.ms = this->ck.getElapsedTime().asMilliseconds();
	pi.t = type;
	pi.panel_no = panel_no;
	pi.j = jubeat_online::game::Judge::NOJUDGE;

	this->no_judge_list->push_back(pi);
}

unsigned int jubeat_online::game::PlayRecord::getTime() const
{
	return this->ck.getElapsedTime().asMicroseconds();
}

const jubeat_online::game::PlayRecord::PanelInput * jubeat_online::game::PlayRecord::getJudgedInput(const size_t idx) const
{
	if(idx < this->judged_list.size())	return &this->judged_list[idx];
	return nullptr;
}

std::vector<jubeat_online::game::PlayRecord::PanelInput>::const_iterator jubeat_online::game::PlayRecord::getPanelInputFromTime(const unsigned int ms) const
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

std::vector<jubeat_online::game::PlayRecord::PanelInput>::const_iterator jubeat_online::game::PlayRecord::getPanelInputListEnd(void) const
{
	return this->judged_list.end();
}

std::vector<jubeat_online::game::PlayRecord::PanelInput>::const_iterator jubeat_online::game::PlayRecord::getPanelInputListBegin(void) const
{
	return this->judged_list.begin();
}
