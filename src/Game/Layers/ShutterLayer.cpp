#include "ShutterLayer.hpp"

void jubeat_online::game::layers::ShutterLayer::Init()
{
	this->dummy.loadFromFile("media/image/combowhite.png");
	this->dummy.setSmooth(true);
}

void jubeat_online::game::layers::ShutterLayer::Draw()
{
	this->clear(sf::Color(0, 0, 0, 0));
	sf::Sprite sp(this->dummy);
	sp.setPosition(0, 592);
	sp.setScale(768.0f / 760.0f, 768.0f / 760.0f);
	this->draw(sp);
}

void jubeat_online::game::layers::ShutterLayer::Exit()
{
}
