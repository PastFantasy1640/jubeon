#include "StartingUpLogoLayer.hpp"

jubeon::game::layers::StartingUpLogoLayer::StartingUpLogoLayer(jubeon::game::scenes::StartingUpScene * scene)
	: scene(scene)
{
}

void jubeon::game::layers::StartingUpLogoLayer::Init()
{
	this->logo.loadFromFile("media/image/jubeon_logo_P.png");
}

void jubeon::game::layers::StartingUpLogoLayer::Draw()
{
	this->clear(sf::Color::White);



	this->scene->ck.getElapsedTime().asMilliseconds();

}

void jubeon::game::layers::StartingUpLogoLayer::Exit()
{
}
