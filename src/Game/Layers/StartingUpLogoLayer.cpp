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
	this->clearBuffer();


}
