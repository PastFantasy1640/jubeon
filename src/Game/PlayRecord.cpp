#include "PlayRecord.hpp"

#include <fstream>
#include <sstream>   // istringstream

#include "../Systems/Logger.hpp"

#include "JudgeDefinition.hpp"


jubeon::game::PlayRecord::PlayRecord(jubeon::game::Sequence * sequence)
	: sequence(sequence), score(sequence->size())
{
}

jubeon::game::PlayRecord::~PlayRecord()
{/*
	for (auto p : *this) {
		if(p != nullptr) delete p;
	}
*/}


void jubeon::game::PlayRecord::judge(const input::PanelInput panel_input)
{

	Notes::const_iterator end = this->sequence->search(panel_input.ms - JudgeSize::B_POOR);
	Notes::const_iterator ite;
	
	Judge j = NOJUDGE;
	for (ite = this->sequence->search(panel_input.ms - JudgeSize::A_POOR); ite != end; ite++) {
		if (ite->second == nullptr && ite->first.getPanelIndex() == panel_input.panel_no) {
			//判定対象
			if (ite->first.getJustTime() >= panel_input.ms) {
				//Before
				jMillisec distance = ite->first.getJustTime() - panel_input.ms;
				if (distance <= -JudgeSize::B_PERFECT) j = PERFECT;
				else if (distance <= -JudgeSize::B_GREAT) j = GREAT;
				else if (distance <= -JudgeSize::B_GOOD) j = GOOD;
				else if (distance <= -JudgeSize::B_POOR) j = EARLY;	//意味のない判定…だが一応…。
				break;
			}
			else {
				//After
				jMillisec distance = panel_input.ms - ite->first.getJustTime();
				if (distance <= JudgeSize::A_PERFECT) j = PERFECT;
				else if (distance <= JudgeSize::A_GREAT) j = GREAT;
				else if (distance <= JudgeSize::A_GOOD) j = GOOD;
				else if (distance <= JudgeSize::A_POOR) j = LATE;	//意味のない判定…だが一応…。
				break;
			}
		}
	}

	//追加
	std::unique_ptr<JudgedPanelInput> jptr(new JudgedPanelInput(panel_input, j));
	if (j != NOJUDGE) {
		this->sequence->setJudgedPanelInput(ite, jptr.get());
		this->score.incJudgeCount(j);
	}
	this->emplace_back(std::move(jptr));

}

bool jubeon::game::PlayRecord::writeToFile(const std::string dst) const
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
	for (auto p = this->begin(); p != this->end(); p++) {
		switch ((*p)->t) {
		case Type::PUSH: type_str = "PUSH"; break;
		case Type::RELEASE: type_str = "RELEASE"; break;
		}

		switch ((*p)->judge) {
		case PERFECT:	judge_str = "PERFECT"; break;
		case GREAT:		judge_str = "GREAT";   break;
		case GOOD:		judge_str = "GOOD";	   break;
		case EARLY:		judge_str = "EARLY";   break;
		case LATE:		judge_str = "LATE";	   break;
		case MISS:		judge_str = "MISS";	   break;
		case NOJUDGE:	judge_str = "NOJUDGE"; break;
		}
		ofst << std::to_string((*p)->ms) << "," << std::to_string((*p)->panel_no) << "," << type_str << "," << judge_str << std::endl;
	}

	systems::Logger::information("プレイ記録ファイルの保存を完了しました");

	return true;
}

bool jubeon::game::PlayRecord::readFromFile(const std::string src)
{
	systems::Logger::information("プレイ記録ファイルの読み込みを開始します。");

	//まず既存のlistを削除
	this->clear();

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
		jMillisec t_ms;
		jPanel t_pno;
		Judge t_judge;
		Type t_type;
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
			t_ms = std::stoi(tmp_vector[0]);
			t_pno = std::stoi(tmp_vector[1]);
		}
		catch (std::invalid_argument e) {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: 数値に変換できません");
			return false;
		}

		//タイプ
		if (tmp_vector[2].compare("PUSH") == 0) t_type = PUSH;
		else if (tmp_vector[2].compare("RELEASE") == 0) t_type = RELEASE;
		else {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: PUSH、RELEASE以外の値が指定されています");
			return false;
		}

		//判定
		if (tmp_vector[3].compare("PERFECT") == 0) t_judge = PERFECT;
		else if (tmp_vector[3].compare("GREAT") == 0) t_judge = GREAT;
		else if (tmp_vector[3].compare("GOOD") == 0) t_judge = GOOD;
		else if (tmp_vector[3].compare("EARLY") == 0) t_judge = EARLY;
		else if (tmp_vector[3].compare("LATE") == 0) t_judge = LATE;
		else if (tmp_vector[3].compare("MISS") == 0) t_judge = MISS;
		else if (tmp_vector[3].compare("NOJUDGE") == 0) t_judge = NOJUDGE;
		else {
			systems::Logger::warning("プレイ記録ファイル" + src + "の文法に間違いがあります。: 判定の値が異常です");
			return false;
		}

		this->emplace_back(new JudgedPanelInput(t_pno,t_type,t_ms,t_judge));
	}

	systems::Logger::information("プレイ記録ファイルの読み込みを完了しました");

	return true;
}


jubeon::game::JudgedPanelInputs::const_iterator jubeon::game::PlayRecord::getIteratorFromTime(const int ms) const
{
	//ラムダ式使ってみる？
	std::function<size_t(size_t, size_t, int)> search = [&](size_t left, size_t right, int ms)
	{
		//探索の左右を指定して、最後に挿入するインデックスの位置を返す
		//終了条件
		if (right == left) return right;

		if (right - 1 == left) {
			if (this->at(left)->ms <= ms) return right;
			else return left;
		}

		//終了しない時
		//ちなみにrightは領域の+1の場所
		size_t center = (left + right) / 2;
		if (this->at(center)->ms <= ms) return search(center, right, ms);
		else return search(left, center, ms);
	};

	size_t idx = search(0, this->size(), ms);

	if (idx > this->size()) {
		//おかしい
		//とりあえずエラー出力
		systems::Logger::warning("二分探索に失敗しています");
		return this->end();
	}

	return this->begin() + idx;
}

const jubeon::game::Score * jubeon::game::PlayRecord::getScore() const
{
	return &this->score;
}
