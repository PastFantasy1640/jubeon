#include "Configures.hpp"

jubeon::models::Configures * jubeon::models::Configures::getInstance(void)
{
	if (!this->conf) this->conf.reset(new Configures);
	return this->conf.get();
}
