#include "FrameLayer.hpp"

void jubeat_online::game::layers::FrameLayer::Init()
{
	//this->frame.loadFromFile("media/image/frame-01.png");
}

void jubeat_online::game::layers::FrameLayer::Draw()
{
	//this->clear(sf::Color(0,0,0,0));
	//s//f::Sprite sp(this->frame);
	//this->draw(sp);

	this->clear(sf::Color(0, 0, 0, 0));

	//実際のサイズに合わせて描写する
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(0, 0, 0, 255));

	//まず上画面
	rect.setSize(sf::Vector2f(768.0f, 130.0f));
	rect.setPosition(sf::Vector2f(0.0f, 463.0f));
	this->draw(rect);

	//それぞれの画面
	//TO DO : 設定ファイルとつき合わせて
	//縦3本
	rect.setSize(sf::Vector2f(38.0f, 897.0f));
	rect.setPosition(sf::Vector2f(164.0f, 463.0f));
	this->draw(rect);

	rect.setPosition(sf::Vector2f(365.0f, 463.0f));
	this->draw(rect);

	rect.setPosition(sf::Vector2f(566.0f, 463.0f));
	this->draw(rect);

	//端っこ1px
	rect.setSize(sf::Vector2f(1.0f, 897.0f));
	rect.setPosition(sf::Vector2f(0.0f, 463.0f));
	this->draw(rect);

	rect.setPosition(sf::Vector2f(767.0f, 463.0f));
	this->draw(rect);

	//横3本
	rect.setSize(sf::Vector2f(768.0f, 38.0f));
	rect.setPosition(sf::Vector2f(0.0f, 756.0f));
	this->draw(rect);

	rect.setPosition(sf::Vector2f(0.0f, 957.0f));
	this->draw(rect);

	rect.setPosition(sf::Vector2f(0.0f, 1158.0f));
	this->draw(rect);

	//端っこ1px
	rect.setSize(sf::Vector2f(768.0f, 1.0f));
	rect.setPosition(sf::Vector2f(0.0f, 1359.0f));
	this->draw(rect);

	


}

void jubeat_online::game::layers::FrameLayer::Exit()
{

}
