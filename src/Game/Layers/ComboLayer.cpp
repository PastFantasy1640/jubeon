#include "ComboLayer.hpp"
#include <time.h>

void jubeon::game::layers::ComboLayer::Init()
{
}

void jubeon::game::layers::ComboLayer::Draw()
{
}

void jubeon::game::layers::ComboLayer::Exit()
{
}

void jubeon::game::layers::ComboLayer::Restart()
{
	if (combo.isUpdate == true) {
		
		this->t0 = clock();

		//y座標をデフォルトに戻す
		this->y = this->y_def;
	}
}

void jubeon::game::layers::ComboLayer::Set_Coordinates()
{
	this->t1 = clock();

	this->t_ = this->t1 - this->t0;

	//上がりきるまでの座標を計算代入
	if (this->t_ <= 40) {
		this->y = this->y_def+1 / 8 * this->t_;
	}

	//下がりきるまでの座標を計算代入
	if (40 < this->t_ <= 160) {
		this->y = this->y_def - 1 / 24 * this->t_;
	}

	//下がりきったあとの座標を計算代入
	if (160 < this->t_) {
		this->y = this->y_def;
	}
}

