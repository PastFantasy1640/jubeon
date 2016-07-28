#include "FrameLayer.hpp"

void jubeat_online::game::layers::FrameLayer::Init()
{
	this->frame.loadFromFile("media/image/frame-01.png");
}

void jubeat_online::game::layers::FrameLayer::Draw()
{
	sf::Sprite sp(this->frame);
	this->clear();
	this->draw(sp);
}

void jubeat_online::game::layers::FrameLayer::Exit()
{

}
