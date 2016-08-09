//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/ListenPanel.hpp"

//for logging
#include "Systems/Logger.hpp"

//for getting resource
#include "Storages/ResourceManager.hpp"
#include "Storages/FontManager.hpp"

//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	std::shared_ptr<jubeon::game::Sequence> sequence,
	std::shared_ptr<jubeon::game::Music> music,
	std::shared_ptr<jubeon::game::PlayRecord> playrecord,
	std::shared_ptr<std::map<const Note *, const JudgedPanelInput *>> seq_pr_mapping,
	std::shared_ptr<jubeon::game::PanelPosition> panel_position,
	int offset_ms)
	: sequence(sequence), music(music), playrecord(playrecord), seq_pr_mapping(seq_pr_mapping), panel_position(panel_position), offset_ms(offset_ms)
{
}


/*
void jubeon::game::layers::SequencePlayer::process(void)
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
*/

//Initialize
void jubeon::game::layers::SequencePlayer::Init()
{
	//初期化処理

	//パネル枠の読み込み
	storage::ResourceManager::getTexture("media/image/panel_shadow.png");



	//###################TEMPORARY####################
	//マーカーマネージャ－みたいなのを用意する
	//マーカー読み込みテスト
	this->mk.reset(new Marker("media/marker/shutter","shutter.json"));
	if (!this->mk->load()) {
		systems::Logger::error("マーカーが読み込めませんでした");
	}


	//画面プッシュは無し
	this->pushing = 0;
}

void jubeon::game::layers::SequencePlayer::Draw()
{
	//画面クリア
	this->clearBuffer();

	//描写
	//Musicに問い合わせて今の再生時刻を取得
	const int mms = this->music->getPlayingCurrentTime();
	const int ms = this->music->getPlayingCurrentTime() - this->offset_ms;



	//### 譜面の描写 ###
	//譜面表示の可能性のあるmsは、CurrentMS - (disappear_time * 2)から、CurrentMS + appear_time
	//全て最高500msであると仮定して
	const int start_ms = ms - 1000;
	const int end_ms = ms + 500;

	//まずms以降のSequenceのイテレータを取得
	std::vector<Note>::const_iterator ite_n = this->sequence->search(start_ms);

	//それ以降でマッピングを確認していく
	for (; ite_n != this->sequence->end(); ite_n++) {
		if (ite_n->getJustTime() > end_ms) break;	//描写範囲外

		//マッピングがあるか
		
		const std::map<const Note *, const JudgedPanelInput *>::const_iterator jpi = this->seq_pr_mapping->find(&(*ite_n));
		if (jpi != this->seq_pr_mapping->end()) {
			//あった
			//ということはすでに判定が終わっている場合である。
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(ms - jpi->second->ms, jpi->second->judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(jpi->second->panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//なかった
			//まだ終わってない
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite_n->getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(ite_n->getPanelIndex());

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		
		}
	}





	//### パネルフレームの表示 ###
	//どのパネルが押されていたか、前回調査したmsを記録しておく ->before_check_ms

	//もしも、bcm以前にPanelInputを追加する場合は、bcmをその時間まで引き戻して記録する。
	//まず、bcmの時間の場所をに二分探索にて探し出す
	auto p = this->playrecord->getIteratorFromTime(*this->playrecord->getJudgedList(), this->before_check_ms);
	
	//前回調査と今回調査のmsが同じ場合はスキップしていい。
	//違う場合のみ更新
	if (this->before_check_ms != mms) {

		//それ以降から、現在のmsまでを線形解析し、パネルの押下状態を更新する
		for (; p != this->playrecord->getJudgedList()->end(); p++) {
			//その情報をもとに、押下による枠縁のグラデーション描写、もしくは、ホールド譜面の描写に使う。
			if ((*p).ms > mms) break;	//今より新しいところへ行った場合、解析は終了

			if ((*p).t) {
				//押下
				this->setPushing((*p).panel_no);
			}
			else {
				//離した
				this->setReleasing((*p).panel_no);
			}

			//もしも、曲を巻き戻したりして、描写を一新しなければならない場合、bcmに0msを指定し、全更新しなくてはならない。

		}

		this->before_check_ms = mms - 1000;

	}

	sf::Text text("ms:" + std::to_string(ms), storage::FontManager::getFont("media/fonts/Frutiger.TTF"));
	text.setColor(sf::Color::Black);
	this->draw(text);
	text.setString("mms:" + std::to_string(mms));
	text.setPosition(0, 100);
	this->draw(text);
	text.setString("panelms:" + std::to_string(input::ListenPanel::panel_clock_->getElapsedTime().asMilliseconds() - input::ListenPanel::offset));
	text.setPosition(0, 130);
	this->draw(text);
	text.setString("diff ms:" + std::to_string(input::ListenPanel::panel_clock_->getElapsedTime().asMilliseconds() - input::ListenPanel::offset - mms));
	text.setPosition(0, 160);
	this->draw(text);

	//最終的にpushされてる場所に描写
	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			const sf::Texture & pframe = storage::ResourceManager::getTexture("media/image/panel_shadow.png");
			sf::Sprite sp(pframe);
			const sf::IntRect & rect = this->panel_position->get(i);

			sp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			sp.setScale(PanelPosition::get_ex(pframe.getSize().x, rect.width), PanelPosition::get_ex(pframe.getSize().y, rect.height));
			this->draw(sp);
		}
	}
}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

