#pragma once

#ifndef JUBEON_STORAGE_FONTMANAGER_HPP
#define JUBEON_STORAGE_FONTMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace storage {
		class FontManager {
		public:
			static const sf::Font & getFont(const std::string fpath);
			static void deleteFont(const std::string fpath);
		private:

			static std::map<std::string, sf::Font> fonts;
		};
	}
}

#endif