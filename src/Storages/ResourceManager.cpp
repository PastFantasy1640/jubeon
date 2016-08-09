//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.cpp
//////////////////////////////////////////////////////
#include "ResourceManager.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


//////////////////////////////////////////////////////
// TEXTURE
//////////////////////////////////////////////////////
template<> std::unordered_map<std::string, sf::Texture> jubeon::storage::ResourceManager<sf::Texture>::data;

template<> const sf::Texture & jubeon::storage::ResourceManager<sf::Texture>::get(const std::string fpath)
{
	//ストレージにあるかどうか
	if (data.count(fpath) == 0) {
		//無いならロードする
		data[fpath].loadFromFile(fpath);
		data[fpath].setSmooth(true);
	}

	return data[fpath];
}

template<> void jubeon::storage::ResourceManager<sf::Texture>::erase(const std::string fpath)
{
	data.erase(fpath);
}


//////////////////////////////////////////////////////
// SOUND
//////////////////////////////////////////////////////
template<> std::unordered_map<std::string, sf::SoundBuffer> jubeon::storage::ResourceManager<sf::SoundBuffer>::data;

template<> const sf::SoundBuffer & jubeon::storage::ResourceManager<sf::SoundBuffer>::get(const std::string fpath)
{
	//ストレージにあるかどうか
	if (data.count(fpath) == 0) {
		//無いならロードする
		data[fpath].loadFromFile(fpath);
	}

	return data[fpath];
}

template<> void jubeon::storage::ResourceManager<sf::SoundBuffer>::erase(const std::string fpath)
{
	data.erase(fpath);
}


//////////////////////////////////////////////////////
// FONT
//////////////////////////////////////////////////////
template<> std::unordered_map<std::string, sf::Font> jubeon::storage::ResourceManager<sf::Font>::data;

template<> const sf::Font & jubeon::storage::ResourceManager<sf::Font>::get(const std::string fpath)
{
	//ストレージにあるかどうか
	if (data.count(fpath) == 0) {
		//無いならロードする
		data[fpath].loadFromFile(fpath);
	}

	return data[fpath];
}

template<> void jubeon::storage::ResourceManager<sf::Font>::erase(const std::string fpath)
{
	data.erase(fpath);
}

