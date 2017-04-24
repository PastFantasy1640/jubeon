//Interface Header file
#include "SequencePlayer.hpp"

//for std::shared_ptr
#include <memory>

//for DEBUG
#include <iostream>
#include "Input/Event.hpp"

//for logging
#include "Systems/Logger.hpp"


//Constructor
jubeon::game::layers::SequencePlayer::SequencePlayer(
	const Sequence * sequence,
	const Music * music,
	const Player * player,
	const jubeon::game::PanelPosition * panel_position,
	int offset_ms)
	: sequence(sequence), music(music), player(player), panel_position(panel_position), offset_ms(offset_ms)
{
}




//Initialize
void jubeon::game::layers::SequencePlayer::Init()
{
	//初期化処理



}

void jubeon::game::layers::SequencePlayer::Draw()
{
	//画面クリア
	this->clearBuffer();

	//描写
	//Musicに問い合わせて今の再生時刻を取得
	const int mms = this->player->getCurrentTime(this->music);
	const int ms = mms - this->offset_ms;
	
	const int start_ms = ms - this->player->getMarker()->getLengthAfterMax();	//逆なんだな―
	const int end_ms = ms + this->player->getMarker()->getLengthBefore();

	{
		//### 譜面の描写 ###
		//譜面表示の可能性のあるmsは、CurrentMS - (disappear_time * 2)から、CurrentMS + appear_time
		//全て最高500msであると仮定して

		//まずms以降のSequenceのイテレータを取得


		Notes::const_iterator begin = this->sequence->search(start_ms);
		Notes::const_iterator end = this->sequence->search(end_ms);


		for (auto ite = begin; ite != end; ite++) {
			//描写範囲内

			if (ite->second != nullptr) {
				//あった
				//ということはすでに判定が終わっている場合である。
				this->drawMarker(ms - ite->second->ms, ite, ite->second->judge);
			}
			else if (!ite->first.isHoldEnd()) {
				//なかった
				//まだ終わってない
				//Markerのテクスチャを取得
				//ホールドエンドマーカーは描写しない
				this->drawMarker(ms - ite->first.getJustTime(), ite, NOJUDGE);
			}

		}
	}
	
	/*
	開発メモ
	いつものSequenceで描写できないこと→ホールドエンドがSequenceのEndに達していない時
	・holdのsecondがnullptrじゃない
	・endより以降に終わるholdを描写する
	*/
	//ホールドの描写
	{
		for (auto ite = this->player->getPlayRecord()->getHoldingList()->begin(); ite != this->player->getPlayRecord()->getHoldingList()->end(); ite++) {
			if (ite->second != nullptr) {
				jMillisec hold_end_time = ite->first.getJustTime() + ite->first.getHoldDuration();
				if (hold_end_time >= end_ms) {
					//描写
					this->drawMarker(ms - ite->second->ms, ite, ite->second->judge);
				}
			}
		}
	}
}

void jubeon::game::layers::SequencePlayer::Exit()
{
}

void jubeon::game::layers::SequencePlayer::drawMarker(const jMillisec now_ms ,const Notes::const_iterator & ite, Judge judge)
{
	const sf::Texture * tex = this->player->getMarker()->getTexturePtr(now_ms, judge);
	if (tex != nullptr) {

		sf::Sprite markersp(*tex);

		const sf::IntRect & rect = this->panel_position->get(ite->first.getPanelIndex());

		markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
		markersp.setScale(static_cast<double>(rect.width) / tex->getSize().x, static_cast<double>(rect.height) / tex->getSize().y);
		this->draw(markersp);

	}
}

