#include "LayerBase.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../../Systems/Logger.hpp"
#include "../../Systems/Exceptions.hpp"

using namespace jubeon::graphics;


jubeon::graphics::LayerBase::LayerBase()
	: exit_code(0),
	sf::RenderTexture()
{
}

jubeon::graphics::LayerBase::~LayerBase()
{
}

void jubeon::graphics::LayerBase::setExitCode(const int code)
{
	this->exit_code = code;
	if (this->exit_code != 0) {
		jubeat_online::systems::Logger::information("�I���R�[�h" + std::to_string(code) + "�ɂă��C���[���I�����܂��B");
	}
}

unsigned int jubeon::graphics::LayerBase::getExitCode() const {
	return this->exit_code;
}

