#include "Combo.hpp"

unsigned int jubeon::game::Combo::increase(void)
{
	this->combo ++;

	return this->combo;
}

void jubeon::game::Combo::reset(void)
{
	this->combo = 0;
	this->combo_baf = 0;
}

unsigned int jubeon::game::Combo::get(void) const
{
	return this->combo;
}

bool jubeon::game::Combo::isUpdate(void) const
{
	if (this->combo != this->combo_baf) {
		return true;
	}
	return false;
}

void jubeon::game::Combo::clearUpdateCount(void)
{
	this->combo_baf = this->combo;
}

jubeon::game::Combo::Combo()
{
	this->combo = 0;
	this->combo_baf = 0;
}

jubeon::game::Combo::~Combo()
{
}
