#include "Configures.hpp"


std::unique_ptr<jubeon::models::Configures> jubeon::models::Configures::conf;

jubeon::models::Configures * jubeon::models::Configures::getInstance(void)
{
	if (!conf) conf.reset(new Configures);
	return conf.get();
}
