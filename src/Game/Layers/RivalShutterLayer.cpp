#include "RivalShutterLayer.hpp"

#include "Storages/Resource.hpp"

using namespace jubeon::storages;

jubeon::game::layers::RivalShutterLayer::RivalShutterLayer(const sf::Vector2f position, const std::shared_ptr<Music>& music, const Difficulty & difficulty)
	: music(music), difficulty(difficulty), enable(true)
{
	this->buffer_sprite.setPosition(position);
}

jubeon::game::layers::RivalShutterLayer::RivalShutterLayer(const sf::Vector2f position)
	: enable(false), music(), difficulty()
{
	this->buffer_sprite.setPosition(position);
}

void jubeon::game::layers::RivalShutterLayer::Init()
{
	this->createBuffer(sf::Vector2u(192,192));

	//�v���C���[�����鎞�Ƃ��Ȃ����Ŕw�i���؂��ւ���
	if (this->enable) {
		Resource::setf("media/image/combowhite.png", Resource::TEX);
		Resource::setf("media/image/rival_frame.png", Resource::TEX);
		switch (this->difficulty) {
		case BASIC:		Resource::setf("media/image/rival_basic_frame.png", Resource::TEX); break;
		case ADVANCED:	Resource::setf("media/image/rival_advanced_frame.png", Resource::TEX); break;
		case EXTREME:	Resource::setf("media/image/rival_extreme_frame.png", Resource::TEX); break;
		}
	}
	else {
		Resource::setf("media/image/default_rival.png", Resource::TEX);
	}
}


void jubeon::game::layers::RivalShutterLayer::Draw()
{
	this->clearBuffer();

	if (this->enable) {
		//####################TEMPORARY
		sf::Sprite tmp(*Resource::setf("media/image/combowhite.png", Resource::TEX).gett());
		tmp.setScale(0.25263, 0.25263);
		this->draw(tmp);

		sf::Sprite sp;
		switch (this->difficulty) {
		case BASIC:		sp.setTexture(*Resource::setf("media/image/rival_basic_frame.png", Resource::TEX).gett()); break;
		case ADVANCED:	sp.setTexture(*Resource::setf("media/image/rival_advanced_frame.png", Resource::TEX).gett()); break;
		case EXTREME:	sp.setTexture(*Resource::setf("media/image/rival_extreme_frame.png", Resource::TEX).gett()); break;
		}
		this->draw(sp);

		sf::Sprite rival_frame(*Resource::setf("media/image/rival_frame.png", Resource::TEX).gett());

	}
	else {
		//�v���C���[����
		this->draw(sf::Sprite(*Resource::setf("media/image/default_rival.png", Resource::TEX).gett()));
	}
}

void jubeon::game::layers::RivalShutterLayer::Exit()
{
}
