//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.cpp
//////////////////////////////////////////////////////
#include "Resource.hpp"

std::unique_ptr<jubeon::storages::Resource::ResourceManager> jubeon::storages::Resource::ResourceManager::instance;

jubeon::storages::Resource::ResourceManager::~ResourceManager()
{
}

unsigned int jubeon::storages::Resource::ResourceManager::getNextID()
{
	return this->nID++;
}

jubeon::storages::Resource::ResourceManager * jubeon::storages::Resource::ResourceManager::getInstance()
{
	if (!ResourceManager::instance) ResourceManager::instance.reset(new ResourceManager());
	return ResourceManager::instance.get();
}

jubeon::storages::Resource::ResourceManager::ResourceManager()
	: nID(1)
{
}
