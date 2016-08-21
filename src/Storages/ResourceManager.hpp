//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.hpp
//////////////////////////////////////////////////////
#pragma once

#ifndef JUBEON_STORAGE_RESOURCEMANAGER_HPP
#define JUBEON_STORAGE_RESOURCEMANAGER_HPP

#include "ResourceManager.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <unordered_map>
#include <memory>
//Singleton

namespace jubeon {
	namespace storage {
		template<class T>
		class ResourceManager {
		public:
		    /** SINGLETON. get the instance.
		     * @returns Instance of the ResourceManager<T>
		     * @notice You can assign T sf::Texture, sf::SoundBuffer, or sf::Font.
		     */
		    static ResourceManager * getInstance(void);
			
			/** Get the resource instance.
			 * @param fpath the file path of the resource.
			 * @returns constraint reference of the resource instance.
			 */
			const T & get(const std::string fpath);
			
			/** Erase the resouce.
			 * @param fpath the file path of the resource which you want to erace.
			 */
			void erase(const std::string fpath);
			
			/** Clear the all resource.
			 */
			void clear(void);
		private:
		    static std::unique_ptr<ResourceManager<T>> instance; 
		
			std::unordered_map<std::string, T> data;
		};
	};
};
#endif
