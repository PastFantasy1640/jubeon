//////////////////////////////////////////////////////
// (c) 2016 white ResourceManager.hpp
//////////////////////////////////////////////////////
#pragma once

#ifndef JUBEON_STORAGE_RESOURCEMANAGER_HPP
#define JUBEON_STORAGE_RESOURCEMANAGER_HPP

#include <unordered_map>

namespace jubeon {
	namespace storage {
		template<typename T>
		class ResourceManager {
		public:
			static const T & get(const std::string fpath);
			static void erase(const std::string fpath);
		private:
			static std::unordered_map<std::string, T> data;
		};
	}
}

#endif
