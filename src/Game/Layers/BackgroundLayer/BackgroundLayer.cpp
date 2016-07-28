#include "BackgroundLayer.hpp"

void jubeat_online::game::layers::BackgroundLayer::Init()
{
	this->background.loadFromFile("media/image/haikei-01.png");
}

void jubeat_online::game::layers::BackgroundLayer::Draw()
{
	sf::Sprite sp(this->background);
	this->clear();
	this->draw(sp);
}

void jubeat_online::game::layers::BackgroundLayer::Exit()
{

}
