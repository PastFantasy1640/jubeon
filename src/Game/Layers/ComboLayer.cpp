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
		
		//時間を0に
		clock.restart();

		//y座標をデフォルトに戻す
		this->y = this->y_def;

	}
}

void jubeon::game::layers::ComboLayer::set_Coordinates()
{
	this->t = this->clock.getElapsedTime().asMilliseconds();

	//this->t_ = this->t1 - this->t0;

	//上がりきるまでの座標を計算代入
	if (this->t <= 40) {
		this->y = this->y_def+1 / 8 * this->t;
	}

	//下がりきるまでの座標を計算代入
	if (40 < this->t && this->t <= 160) {
		this->y = this->y_def - 1 / 24 * this->t;
	}

	//下がりきったあとの座標を計算代入
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

