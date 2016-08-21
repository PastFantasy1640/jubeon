//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.cpp
//////////////////////////////////////////////////////
#include "ResourceManager.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"



//////////////////////////////////////////////////////
// explicit instantiation
//////////////////////////////////////////////////////
template class jubeon::storage::ResourceManager<sf::Texture>;
template class jubeon::storage::ResourceManager<sf::SoundBuffer>;
template class jubeon::storage::ResourceManager<sf::Font>;

//////////////////////////////////////////////////////
// Singleton Structure
//////////////////////////////////////////////////////
/*
template<> std::unique_ptr<jubeon::storage::ResourceManager<sf::Texture>> jubeon::storage::ResourceManager<sf::Texture>::instance;

template<> std::unique_ptr<jubeon::storage::ResourceManager<sf::SoundBuffer>> jubeon::storage::ResourceManager<sf::SoundBuffer>::instance;

template<> std::unique_ptr<jubeon::storage::ResourceManager<sf::Font>> jubeon::storage::ResourceManager<sf::Font>::instance;
*/

template< class T> std::unique_ptr<jubeon::storage::ResourceManager<T>> jubeon::storage::ResourceManager<T>::instance;


template<class T>
jubeon::storage::ResourceManager<T> * 
jubeon::storage::ResourceManager<T>::getInstance(void)
{
    if(ResourceManager<T>::instance) ResourceManager<T>::instance.reset(new ResourceManager<T>);
    return ResourceManager<T>::instance.get();
}


//////////////////////////////////////////////////////
// MEMBERS
//////////////////////////////////////////////////////
template<class T> 
const T & jubeon::storage::ResourceManager<T>::get
(const std::string fpath)
{
	//Check the data exists.
	if (this->data.count(fpath) == 0) {
		//There is no data matched fpath.
		this->data[fpath].loadFromFile(fpath);
	}

    //Return the reference of the data.
	return this->data[fpath];
}

template<class T>
void jubeon::storage::ResourceManager<T>::erase
(const std::string fpath)
{
    //Erase the data.
    this->data.erase(fpath);
}

template<class T>
void jubeon::storage::ResourceManager<T>::clear()
{
    //Clear all data.
    this->data.clear();
}

