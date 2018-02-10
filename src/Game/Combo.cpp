#include "Combo.hpp"

unsigned int jubeon::Combo::increase(void)
{
	this->combo ++;

	return this->combo;
}

void jubeon::Combo::reset(void)
{
	this->combo = 0;
	this->combo_baf = 0;
}

unsigned int jubeon::Combo::get(void) const
{
	return this->combo;
}

bool jubeon::Combo::isUpdate(void) const
{
	if (this->combo != this->combo_baf) {
		return true;
	}
	return false;
}

void jubeon::Combo::clearUpdateCount(void)
{
	this->combo_baf = this->combo;
}

jubeon::Combo::Combo() : combo(0), combo_baf(0)
{
}

jubeon::Combo::~Combo()
{
}
