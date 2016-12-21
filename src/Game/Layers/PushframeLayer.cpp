#include "PushframeLayer.hpp"
#include "Storages/ResourceManager.hpp"

jubeon::game::layers::PushframeLayer::PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music)
	: playrecord(), panelposition(panelposition), music(music)
{
}

jubeon::game::layers::PushframeLayer::PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music, const std::shared_ptr<PlayRecord>& playrecord)
	: playrecord(playrecord), panelposition(panelposition), music(music)
{
}

void jubeon::game::layers::PushframeLayer::Init()
{

	//パネル枠の読み込み
	storages::Resource res = storages::Resource::setf("media/image/panel_shadow.png", storages::Resource::TEX);
	storages::Resource::setKey("panel_shadow", res);
	
	//画面プッシュは無し
	this->pushing = 0;

}

void jubeon::game::layers::PushframeLayer::Draw()
{
	//画面クリア
	this->clearBuffer();

	jMillisec mms = this->music->getPlayingCurrentTime();

	if (this->playrecord) {
		//再生の時

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

			this->before_check_ms = mms;
		}
	}

	//最終的にpushされてる場所に描写
	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			const sf::Texture & pframe = *storages::Resource::setk("panel_shadow").gett();
			sf::Sprite sp(pframe);
			const sf::IntRect & rect = this->panelposition->get(i);

			sp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			sp.setScale(PanelPosition::get_ex(pframe.getSize().x, rect.width), PanelPosition::get_ex(pframe.getSize().y, rect.height));
			this->draw(sp);
		}
	}
}

void jubeon::game::layers::PushframeLayer::Exit()
{

}
