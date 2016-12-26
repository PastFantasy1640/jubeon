#include "PushframeLayer.hpp"
#include "Storages/ResourceManager.hpp"



jubeon::game::layers::PushframeLayer::PushframeLayer(const jubeon::game::PanelPosition * panelposition, strbuf::StreamBuffer<input::PanelInput> * pinput_sb)
	: poutput_que(new strbuf::OutputStream<input::PanelInput>()),
	panel_position(panelposition)
{
	pinput_sb->addOutputStream(this->poutput_que);
}

void jubeon::game::layers::PushframeLayer::Init()
{

	//パネル枠の読み込み
	storages::Resource::setf("media/image/panel_shadow.png", storages::Resource::TEX).setKey("panel_shadow");
	
	//画面プッシュは無し
	this->pushing = 0;

}

void jubeon::game::layers::PushframeLayer::Draw()
{
	//画面クリア
	this->clearBuffer();

	while (this->poutput_que->getQueSize()) {
		input::PanelInput p = this->poutput_que->unque();
		if (p.t == PUSH) this->setPushing(p.panel_no);
		else this->setReleasing(p.panel_no);
	}
	//最終的にpushされてる場所に描写
	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			const sf::Texture & pframe = *storages::Resource::setk("panel_shadow").gett();
			sf::Sprite sp(pframe);
			const sf::IntRect & rect = this->panel_position->get(i);

			sp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			sp.setScale(PanelPosition::get_ex(pframe.getSize().x, rect.width), PanelPosition::get_ex(pframe.getSize().y, rect.height));
			this->draw(sp);
		}
	}
}

void jubeon::game::layers::PushframeLayer::Exit()
{

}
