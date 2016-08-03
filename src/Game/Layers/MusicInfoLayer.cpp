#include "MusicInfoLayer.hpp"

void jubeon::game::layers::MusicInfoLayer::Init()
{
	this->dummy.loadFromFile("media/image/top.png");
}

void jubeon::game::layers::MusicInfoLayer::Draw()
{
	sf::Sprite sp(this->dummy);
	sp.setPosition(28, 24);
	this->clearBuffer();
	this->draw(sp);
}

void jubeon::game::layers::MusicInfoLayer::Exit()
{

}
