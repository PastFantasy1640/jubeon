#pragma once

#ifndef JUBEON_STORAGE_RESOURCEMANAGER_HPP
#define JUBEON_STORAGE_RESOURCEMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace jubeon {
	namespace storage {
		class ResourceManager{
		public:
			static const sf::Texture & getTexture(const std::string fpath);
			static void deleteTexture(const std::string fpath);
			static const sf::SoundBuffer & getSoundBuffer(const std::string fpath);
			static void deleteSound(const std::string fpath);
		private:

			static std::map<std::string, sf::Texture> textures;
			static std::map<std::string, sf::SoundBuffer> sounds;
		};
	}
}

#endif