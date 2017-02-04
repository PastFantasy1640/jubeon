#include "ComboLayer.hpp"

void jubeon::game::layers::ComboLayer::Init()
{
}

void jubeon::game::layers::ComboLayer::Draw()
{
}

void jubeon::game::layers::ComboLayer::Exit()
{
}

void jubeon::game::layers::ComboLayer::restart()
{
	if (combo->isUpdate() == true) {
		
		//���Ԃ�0��
		clock.restart();

		//y���W���f�t�H���g�ɖ߂�
		this->y = this->y_def;

	}
}

void jubeon::game::layers::ComboLayer::set_Coordinates()
{
	this->t = this->clock.getElapsedTime().asMilliseconds();

	//this->t_ = this->t1 - this->t0;

	//�オ�肫��܂ł̍��W���v�Z���
	if (this->t <= 40) {
		this->y = this->y_def+1 / 8 * this->t;
	}

	//�����肫��܂ł̍��W���v�Z���
	if (40 < this->t && this->t <= 160) {
		this->y = this->y_def - 1 / 24 * this->t;
	}

	//�����肫�������Ƃ̍��W���v�Z���
	if (160 < this->t) {
		this->y = this->y_def;
	}
}

jubeon::game::layers::ComboLayer::ComboLayer()
{
}

jubeon::game::layers::ComboLayer::~ComboLayer()
{
}

