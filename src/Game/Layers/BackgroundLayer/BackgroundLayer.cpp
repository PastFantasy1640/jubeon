#include "BackgroundLayer.hpp"
#include <math.h>
#define PI 3.1415926535
#include <random>

jubeat_online::game::layers::BackgroundLayer::BackgroundLayer()
{
}

void jubeat_online::game::layers::BackgroundLayer::Init()
{
	//this->background.loadFromFile("media/image/haikei-01.png");


	this->drop1.reset(new Theme::Drop<5>(genRandomPoints<5>(350), 10));
	this->drop1->setFillColor(sf::Color(0x45D5FEff));
	this->drop1->setPosition(500, 500);

	this->drop2.reset(new Theme::Drop<5>(genRandomPoints<5>(280), 10));
	this->drop2->setFillColor(sf::Color(0xff3a7dff));
	this->drop2->setPosition(380, 520);
	
}

void jubeat_online::game::layers::BackgroundLayer::Draw()
{
	this->clear(sf::Color::White);
	this->drop1->applyForce(sf::Vector2f(5, 0));
	this->draw(*(this->drop1));

	this->drop2->applyForce(sf::Vector2f(-90, 0));
	this->draw(*(this->drop2),sf::BlendMultiply);
	//sf::Sprite sp(this->background);
	//this->clear();
	//this->draw(sp);
}

void jubeat_online::game::layers::BackgroundLayer::Exit()
{

}

template<std::size_t S>
std::array<sf::Vector2f, S> jubeat_online::game::layers::BackgroundLayer::genRandomPoints(unsigned int r)
{
	// å‹äpå`ÇÃäeí∏ì_Çê∂ê¨
	std::array<sf::Vector2f, S> points;
	std::random_device rnd;
	for (int i = 0; i < points.size(); i++) {

		float degree = i * 360 / static_cast<float>(S);
		float scale = 1 - (static_cast<double>(rnd()) / 0xffffffff) / 3.0f;
		float tx = cos(degree * PI / 180.0f) * r;
		float ty = sin(degree * PI / 180.0f) * r;
		points[i] = (sf::Vector2f(scale * tx, scale * ty));
	}
	return points;
}