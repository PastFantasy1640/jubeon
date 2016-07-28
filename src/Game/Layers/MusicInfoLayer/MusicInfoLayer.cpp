#include "MusicInfoLayer.hpp"

void jubeat_online::game::layers::MusicInfoLayer::Init()
{
	this->dummy.loadFromFile("media/image/top.png");
}

void jubeat_online::game::layers::MusicInfoLayer::Draw()
{
	sf::Sprite sp(this->dummy);
	sp.setPosition(28, 24);
	this->clear();
	this->draw(sp);
}

void jubeat_online::game::layers::MusicInfoLayer::Exit()
{

}
