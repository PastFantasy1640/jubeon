//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/ListenPanel.hpp"

//for logging
#include "Systems/Logger.hpp"


//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	std::shared_ptr<jubeon::game::Sequence> sequence,
	std::shared_ptr<jubeon::game::Music> music,
	std::shared_ptr<jubeon::game::PlayRecord> playrecord,
	std::shared_ptr<std::map<const size_t, size_t>> seq_pr_mapping,
	std::shared_ptr<jubeon::game::PanelPosition> panel_position,
	int offset_ms)
	: sequence(sequence), music(music), playrecord(playrecord), seq_pr_mapping(seq_pr_mapping), panel_position(panel_position), offset_ms(offset_ms)
{
}




//Initialize
void jubeon::game::layers::SequencePlayer::Init()
{
	//初期化処理




	//###################TEMPORARY####################
	//マーカーマネージャ－みたいなのを用意する
	//マーカー読み込みテスト
	this->mk.reset(new Marker("media/marker/shutter","shutter.json"));
	if (!this->mk->load()) {
		systems::Logger::error("マーカーが読み込めませんでした");
	}


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
	size_t sequence_idx = std::distance(this->sequence->begin(), ite_n);

	//それ以降でマッピングを確認していく
	for (; sequence_idx < this->sequence->size(); sequence_idx++){
		if (this->sequence->at(sequence_idx).getJustTime() > end_ms) break;	//描写範囲外

		//マッピングがあるか
		
		const std::map<const size_t, size_t>::const_iterator jpi = this->seq_pr_mapping->find(sequence_idx);
		if (jpi != this->seq_pr_mapping->end()) {
			//あった
			//ということはすでに判定が終わっている場合である。
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(mms - this->playrecord->getJudgedList()->at(jpi->second).ms, this->playrecord->getJudgedList()->at(jpi->second).judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(this->playrecord->getJudgedList()->at(jpi->second).panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//なかった
			//まだ終わってない
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(ms - this->sequence->at(sequence_idx).getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(this->sequence->at(sequence_idx).getPanelIndex());

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		
		}
	}




}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

