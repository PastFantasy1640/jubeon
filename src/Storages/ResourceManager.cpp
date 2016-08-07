#include "ResourceManager.hpp"

const sf::Texture & jubeon::storage::ResourceManager::getTexture(const std::string fpath)
{
	//ストレージにあるかどうか
	if (textures.count(fpath) == 0) {
		//無いならロードする
		textures[fpath].loadFromFile(fpath);
		textures[fpath].setSmooth(true);
	}

	return textures[fpath];
}

void jubeon::storage::ResourceManager::deleteTexture(const std::string fpath)
{
	textures.erase(fpath);
}

const sf::SoundBuffer & jubeon::storage::ResourceManager::getSoundBuffer(const std::string fpath)
{
	//ストレージにあるかどうか
	if (sounds.count(fpath) == 0) {
		//無いならロードする
		sounds[fpath].loadFromFile(fpath);
	}

	return sounds[fpath];
}

void jubeon::storage::ResourceManager::deleteSound(const std::string fpath)
{
	sounds.erase(fpath);
}
