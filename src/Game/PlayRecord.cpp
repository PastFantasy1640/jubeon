#include "PlayRecord.hpp"

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
	//追加
	this->addJudged(JudgedPanelInput(p, judge));
}

void jubeon::game::PlayRecord::addJudged(const JudgedPanelInput judged_p)
{
	//リストへ追加
	this->judged_list->push_back(judged_p);
}

bool jubeon::game::PlayRecord::writeToFile(const std::string dst)
{
	//書き出し
	//書式->ASCII
	//date:"20xx-xx-xx xx:xx:xx"
	//name:"wHite"
	//[ms],[panel],[type],[judge]
	//以後EOFまで

	systems::Logger::information("プレイ記録ファイルの保存を開始します。");

	//ファイルストリーム
	std::ofstream ofst(dst, std::ios::trunc);

	if (!ofst) {
		systems::Logger::warning("プレイ記録ファイル" + dst + "を作成できませんでした。記録は中止されます。");
		return false;
	}

	//ヘッダの追加
	ofst << "date:" + this->date << std::endl;
	ofst << "name:" + this->name << std::endl;

	//情報の書き出し
	std::string type_str;
	std::string judge_str;
	for (auto p = this->judged_list->begin(); p != this->judged_list->end(); p++) {
		switch (p->t) {
		case input::Type::PUSH: type_str = "PUSH"; break;
		case input::Type::RELEASE: type_str = "RELEASE"; break;
		}

		switch (p->judge) {
		case PERFECT:	judge_str = "PERFECT";
		case GREAT:		judge_str = "GREAT";
		case GOOD:		judge_str = "GOOD";
		case EARLY:		judge_str = "EARLY";
		case LATE:		judge_str = "LATE";
		case MISS:		judge_str = "MISS";
		case NOJUDGE:	judge_str = "NOJUDGE";
		}
		ofst << std::to_string(p->ms) << "," << std::to_string(p->panel_no) << "," << type_str << "," << judge_str << std::endl;
	}

	systems::Logger::information("プレイ記録ファイルの保存を完了しました");

	return true;
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


