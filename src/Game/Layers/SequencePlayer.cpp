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
	const int mms = this->player->getCurrentTime(this->music);
	const int ms = mms - this->offset_ms;



	//### 譜面の描写 ###
	//譜面表示の可能性のあるmsは、CurrentMS - (disappear_time * 2)から、CurrentMS + appear_time
	//全て最高500msであると仮定して
	const int start_ms = ms - this->mk->getLengthAfterMax();	//逆なんだな―
	const int end_ms = ms + this->mk->getLengthBefore();

	//まずms以降のSequenceのイテレータを取得
	Notes::const_iterator begin = this->sequence->search(start_ms);
	Notes::const_iterator end = this->sequence->search(end_ms);

	for (auto ite = begin; ite != end; ite++) {
		//描写範囲内

		if (ite->second != nullptr) {
			//あった
			//ということはすでに判定が終わっている場合である。
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite->second->ms, ite->second->judge);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);

				const sf::IntRect & rect = this->panel_position->get(ite->second->panel_no);

				markersp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
				markersp.setScale(PanelPosition::get_ex(tex->getSize().x, rect.width), PanelPosition::get_ex(tex->getSize().y, rect.height));
				this->draw(markersp);

			}
		}
		else {
			//なかった
			//まだ終わってない
			//Markerのテクスチャを取得
			const sf::Texture * tex = this->mk->getTexturePtr(ms - ite->first.getJustTime(), NOJUDGE);
			if (tex != nullptr) {

				sf::Sprite markersp(*tex);
				const sf::IntRect & rect = this->panel_position->get(ite->first.getPanelIndex());

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

