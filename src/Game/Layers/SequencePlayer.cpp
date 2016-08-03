#include "SequencePlayer.hpp"

#include <memory>

#include <iostream>

#include "../PlayRecord.hpp"
#include "../../Input/PanelEvent.hpp"

jubeat_online::game::layers::SequencePlayer::SequencePlayer(const Sequence * sequence, Music * music, std::unique_ptr<PlayRecord> playrecord)
	: LayerBase(),
	sequence(sequence),
	music(music),
	playrecord(std::move(playrecord)),
	before_check_ms(0),
	pushing(0),
	mk("media/marker/shutter", "shutter.json")
{
}

void jubeat_online::game::layers::SequencePlayer::process(void)
{
	//process関数では、譜面の判定を行います。
	
	//PlayRecordから未判定分を取得する
	PlayRecord::NoJudgedList no_judge_list = this->playrecord->getNoJudgedList();

	//Sequenceからインスタンスを取得する
	//取得済みです（メンバ）

	//判定処理
	//TO DO : 判定
	//今のところ全てNOJUDGE
	unsigned int music_ms = this->music->getPlayingCurrentTime();
	unsigned int panel_ms = this->playrecord->getTime();
	int diff_ms = panel_ms - music_ms;

	for (auto p : *no_judge_list) {
		p.j = Judge::NOJUDGE;	//TEMPORARY
		p.ms -= diff_ms;	//曲のmsへ
		if (p.ms <= this->before_check_ms) this->before_check_ms = p.ms;	//引き戻す
	}

	//PlayRecordへ判定を更新
	this->playrecord->setJudgedList(std::move(no_judge_list));

	//ShutterLayerを適宜更新
	//TO DO : まだやってない

	//MusicBarを適宜更新
	//TO DO : まだ(ry
}

void jubeat_online::game::layers::SequencePlayer::Init()
{
	//初期化処理

	//パネル枠の読み込み
	this->panel_frame.loadFromFile("media/image/panel_shadow.png");
	//panel_shadow.pngはサイズ190x190
	//伸縮させる可能性があるので、smooth適用
	this->panel_frame.setSmooth(true);

	//マーカー読み込みテスト
	this->mk.load();


}

void jubeat_online::game::layers::SequencePlayer::Draw()
{

	this->clearBuffer();

	//描写

	//Musicに問い合わせて今の再生時刻を取得
	const unsigned int ms = this->music->getPlayingCurrentTime();

	//Sequenceからインスタンスを取得
	//済

	//PlayRecordからインスタンスを取得
	//済、というか持ってる

	//Markerのテクスチャを取得
	const sf::Texture * tex = this->mk.getTexturePtr((this->music->getPlayingCurrentTime() % 2000) - 1000, PERFECT);
	if (tex != nullptr) {

		sf::Sprite markersp(*tex);
		markersp.setPosition(100, 100);
		markersp.setScale(163.0f / tex->getSize().x, 163.0f / tex->getSize().y);
		this->draw(markersp);

	}
	//描写


	//*****************とりあえず今はテストとして、

	//Markerのテクスチャ取得はあとだな
	//perfectタイムを0msとして、それよりも早い場合は負のms、遅い場合は正のms
	//指定して関数を呼べば、対応するマーカーフレームのテクスチャが返される
	//それで描写、ok
	
	auto to_binString = [](unsigned int val)
	{
		if (!val)
			return std::string("0");
		std::string str;
		while (val != 0) {
			if ((val & 1) == 0)  // val は偶数か？
				str.insert(str.begin(), '0');  //  偶数の場合
			else
				str.insert(str.begin(), '1');  //  奇数の場合
			val >>= 1;
		}
		return str;
	};


	//押されてるときのマーカー反応をやろう
	//どのパネルが押されていたか、前回調査したmsを記録しておく ->before_check_ms

	//もしも、bcm以前にPanelInputを追加する場合は、bcmをその時間まで引き戻して記録する。
	//まず、bcmの時間の場所をに二分探索にて探し出す
	auto p = this->playrecord->getPanelInputFromTime(this->before_check_ms);
	
	//前回調査と今回調査のmsが同じ場合はスキップしていい。
	//違う場合のみ更新
	if (this->before_check_ms != ms) {

		//それ以降から、現在のmsまでを線形解析し、パネルの押下状態を更新する
		for (; p != this->playrecord->getPanelInputListEnd(); p++) {
			//その情報をもとに、押下による枠縁のグラデーション描写、もしくは、ホールド譜面の描写に使う。
			if ((*p).ms > ms) break;	//今より新しいところへ行った場合、解析は終了

			if ((*p).t) {
				//押下
				this->setPushing((*p).panel_no);
				std::cout << "調査" << ms << "ms:前回" << this->before_check_ms << "ms:" << to_binString(this->pushing) << "\n";
			}
			else {
				//離した
				this->setReleasing((*p).panel_no);
				std::cout << "調査" << ms << "ms:" << to_binString(this->pushing) << "\n";
			}

			//もしも、曲を巻き戻したりして、描写を一新しなければならない場合、bcmに0msを指定し、全更新しなくてはならない。

		}

		this->before_check_ms = ms;

	}

	//最終的にpushされてる場所に描写
	//TO DO : パネル情報と照らし合わせながら

	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			//sf::RectangleShape test(sf::Vector2f(163.0f, 163.0f));
			//test.setFillColor(sf::Color::Red);
			//test.setPosition(200 + (i % 4) * 170, 200 + (i / 4) * 170);
			//枠の大きさは163
			//枠の太さは38
			//0番目のパネルの左上座標は(1,593)
			sf::Sprite sp(this->panel_frame);
			sp.setPosition(1 + (i % 4) * (163 + 38), 593 + (i / 4) * (163 + 38));
			sp.setScale(163.0f / 190.0f, 163.0f / 190.0f);
			this->draw(sp);
		}
	}



}

void jubeat_online::game::layers::SequencePlayer::Exit()
{
}
