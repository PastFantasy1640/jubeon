#include "FontManager.hpp"

std::map<std::string, sf::Font> jubeon::storage::FontManager::fonts;

const sf::Font & jubeon::storage::FontManager::getFont(const std::string fpath)
{
	//ストレージにあるかどうか
	if (fonts.count(fpath) == 0) {
		//無いならロードする
		fonts[fpath].loadFromFile(fpath);
	}

	return fonts[fpath];
}

void jubeon::storage::FontManager::deleteFont(const std::string fpath)
{
	fonts.erase(fpath);
}
