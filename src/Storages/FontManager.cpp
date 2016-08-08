#include "FontManager.hpp"

std::map<std::string, sf::Font> jubeon::storage::FontManager::fonts;

const sf::Font & jubeon::storage::FontManager::getFont(const std::string fpath)
{
	//�X�g���[�W�ɂ��邩�ǂ���
	if (fonts.count(fpath) == 0) {
		//�����Ȃ烍�[�h����
		fonts[fpath].loadFromFile(fpath);
	}

	return fonts[fpath];
}

void jubeon::storage::FontManager::deleteFont(const std::string fpath)
{
	fonts.erase(fpath);
}
