#include "PlayRecord.hpp"

#include <fstream>
#include <sstream>   // istringstream

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
	ofst << "date:" << this->date << std::endl;
	ofst << "name:" << this->name << std::endl;
	
	//情報の書き出し
	std::string type_str;
	std::string judge_str;
	for (auto p = this->judged_list->begin(); p != this->judged_list->end(); p++) {
		switch (p->t) {
		case Type::PUSH: type_str = "PUSH"; break;
		case Type::RELEASE: type_str = "RELEASE"; break;
		}

		switch (p->judge) {
		case PERFECT:	judge_str = "PERFECT"; break;
		case GREAT:		judge_str = "GREAT";   break;
		case GOOD:		judge_str = "GOOD";	   break;
		case EARLY:		judge_str = "EARLY";   break;
		case LATE:		judge_str = "LATE";	   break;
		case MISS:		judge_str = "MISS";	   break;
		case NOJUDGE:	judge_str = "NOJUDGE"; break;
		}
		ofst << std::to_string(p->ms) << "," << std::to_string(p->panel_no) << "," << type_str << "," << judge_str << std::endl;
	}

	systems::Logger::information("プレイ記録ファイルの保存を完了しました");

	return true;
}

bool jubeon::game::PlayRecord::readFromFile(const std::string src)
{
	systems::Logger::information("プレイ記録ファイルの読み込みを開始します。");

	//まず既存のlistを削除
	this->judged_list->clear();

	//ファイルストリーム
	std::ifstream ifst(src);

	if (!ifst || ifst.fail()) {
		systems::Logger::warning("プレイ記録ファイル" + src + "を読み込めませんでした。");
		return false;
	}

	//ヘッダの読み込み
	//データの間違いがあれば即終了
	std::string str;
	std::string str2;
	JudgedPanelInput tmp;

	//dateを読み込む
	std::getline(ifst, str);
	if (!str.substr(0, 5).compare("date:") == 0) {
		systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: dateがありません");
		return false;
	}
	this->date = str;

	//nameを読み込む
	std::getline(ifst, str);
	if (!str.substr(0, 5).compare("name:") == 0) {
		systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: nameがありません");
		return false;
	}
	this->name = str;

	//終わるまでループ
	std::vector<std::string> tmp_vector;
	while (!ifst.eof())
	{
		// read by line
		std::getline(ifst, str);

		if (str.compare("") == 0) continue;

		//spilt
		const char delimiter = ',';
		std::istringstream line_separater(str);
		tmp_vector.clear();

		while (std::getline(line_separater, str2, delimiter)) {
			tmp_vector.push_back(str2);
		}

		//おかしい
		if (tmp_vector.size() != 4) {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: 要素数が異常です。");
			return false;
		}

		//分析
		try {
			tmp.ms = std::stoi(tmp_vector[0]);
			tmp.panel_no = std::stoi(tmp_vector[1]);
		}
		catch (std::invalid_argument e) {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: 数値に変換できません");
			return false;
		}

		//タイプ
		if (tmp_vector[2].compare("PUSH") == 0) tmp.t = PUSH;
		else if (tmp_vector[2].compare("RELEASE") == 0) tmp.t = RELEASE;
		else {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: PUSH、RELEASE以外の値が指定されています");
			return false;
		}

		//判定
		if (tmp_vector[3].compare("PERFECT") == 0) tmp.judge = PERFECT;
		else if (tmp_vector[3].compare("GREAT") == 0) tmp.judge = GREAT;
		else if (tmp_vector[3].compare("GOOD") == 0) tmp.judge = GOOD;
		else if (tmp_vector[3].compare("EARLY") == 0) tmp.judge = EARLY;
		else if (tmp_vector[3].compare("LATE") == 0) tmp.judge = LATE;
		else if (tmp_vector[3].compare("MISS") == 0) tmp.judge = MISS;
		else if (tmp_vector[3].compare("NOJUDGE") == 0) tmp.judge = NOJUDGE;
		else {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: 判定の値が異常です");
			return false;
		}

		this->judged_list->push_back(tmp);
	}

	systems::Logger::information("プレイ記録ファイルの読み込みを完了しました");

	return true;
}

const std::shared_ptr<std::vector<jubeon::game::JudgedPanelInput>> jubeon::game::PlayRecord::getJudgedList() const
{
	return this->judged_list;
}

std::vector<jubeon::game::JudgedPanelInput>::const_iterator jubeon::game::PlayRecord::getIteratorFromTime(const std::vector<JudgedPanelInput>& list, const int ms)
{
	//ラムダ式使ってみる？
	std::function<size_t(size_t, size_t, int)> search = [&](size_t left, size_t right, int ms)
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


