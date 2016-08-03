#include "StartingUpLogoLayer.hpp"

jubeon::game::layers::StartingUpLogoLayer::StartingUpLogoLayer(jubeon::game::scenes::StartingUpScene * scene)
	: scene(scene)
{
}

void jubeon::game::layers::StartingUpLogoLayer::Init()
{
	this->logo.loadFromFile("media/image/jubeon_logo_P.png");
	this->logo.setSmooth(true);
}

void jubeon::game::layers::StartingUpLogoLayer::Draw()
{
	this->clear(sf::Color::White);

	sf::Sprite sp(this->logo);
	sp.setOrigin(this->logo.getSize().x / 2, this->logo.getSize().y / 2);
	sp.setPosition(768 / 2 - 30, 200);
	sp.setScale(768.0f / this->logo.getSize().x, 768.0f / this->logo.getSize().x);

	int msec = this->scene->ck.getElapsedTime().asMilliseconds();
	if (msec < 2000) {
		sp.setColor(sf::Color(0, 0, 0, msec * 255 / 2000));
	}
	else if (msec > 4000) {
		sp.setColor(sf::Color(0, 0, 0,  255 - (msec - 4000) * 255 / 1000));
	}


	this->draw(sp);


}

void jubeon::game::layers::StartingUpLogoLayer::Exit()
{
}
