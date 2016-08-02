#include "ShutterLayer.hpp"

void jubeon::game::layers::ShutterLayer::Init()
{
	this->dummy.loadFromFile("media/image/combowhite.png");
	this->dummy.setSmooth(true);
}

void jubeon::game::layers::ShutterLayer::Draw()
{
	this->clearBuffer();
	sf::Sprite sp(this->dummy);
	sp.setPosition(0, 592);
	sp.setScale(768.0f / 760.0f, 768.0f / 760.0f);
	this->draw(sp);
}

void jubeon::game::layers::ShutterLayer::Exit()
{
}
