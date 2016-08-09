#include "LayerBase.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../../Systems/Logger.hpp"
#include "../../Systems/Exceptions.hpp"

using namespace jubeon::graphics;


jubeon::graphics::LayerBase::LayerBase()
	: exit_code(0),
	is_create_buffer(false),
	sf::RenderTexture()
{
}

jubeon::graphics::LayerBase::~LayerBase()
{
}

void jubeon::graphics::LayerBase::prepareBuffer(const sf::Vector2u size)
{
	if (!this->is_create_buffer) {
		this->create(size.x, size.y);
		this->setSmooth(true);
		this->is_create_buffer = true;
	}
}



void jubeon::graphics::LayerBase::setExitCode(const int code)
{
	this->exit_code = code;
	if (this->exit_code != 0) {
		jubeon::systems::Logger::information("終了コード" + std::to_string(code) + "にてレイヤーが終了します。");
	}
}

const sf::Sprite & jubeon::graphics::LayerBase::getSprite(void)
{
	this->display();
	this->sp.setTexture(this->getTexture());
	return this->sp;
}

unsigned int jubeon::graphics::LayerBase::getExitCode() const {
	return this->exit_code;
}

