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


/*

//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.cpp
//////////////////////////////////////////////////////
#include "ResourceManager.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Systems/Logger.hpp"

#include "ResourceMapping.hpp"

//////////////////////////////////////////////////////
// explicit instantiation
//////////////////////////////////////////////////////
template class jubeon::storages::ResourceManager<sf::Texture>;
template class jubeon::storages::ResourceManager<sf::SoundBuffer>;
template class jubeon::storages::ResourceManager<sf::Font>;



//////////////////////////////////////////////////////
// Singleton Structure
//////////////////////////////////////////////////////
template< class T> std::unique_ptr<jubeon::storages::ResourceManager<T>> jubeon::storages::ResourceManager<T>::instance;


template<class T>
jubeon::storages::ResourceManager<T> * 
jubeon::storages::ResourceManager<T>::getInstance(void)
{
	if (!ResourceManager<T>::instance) {
		ResourceManager<T>::instance.reset(new ResourceManager<T>);
		//ResourceManager<T>::instance->loadResourceKeyFile();
	}
    return ResourceManager<T>::instance.get();
}


//////////////////////////////////////////////////////
// MEMBERS
//////////////////////////////////////////////////////
template<class T> 
const T & jubeon::storages::ResourceManager<T>::get
(const std::string fpath)
{
	//Check the data exists.
	if (this->data.count(fpath) == 0) {
		//There is no data matched fpath.
		if (!this->data[fpath].loadFromFile(fpath)) {
			systems::Logger::warning("Failed to load the file." + fpath);
		}
	}

    //Return the reference of the data.
	return this->data[fpath];
}

template<class T>
bool jubeon::storages::ResourceManager<T>::erase
(const std::string fpath)
{
    //Erase the data.
    this->data.erase(fpath);
	return true;
}

template<class T>
void jubeon::storages::ResourceManager<T>::clear()
{
    //Clear all data.
    this->data.clear();
}

*/