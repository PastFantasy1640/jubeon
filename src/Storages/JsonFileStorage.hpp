#pragma once
#include <string>
#include <memory>
#include <type_traits>
#include <fstream>
#include "Models/ModelBase.hpp"

namespace jubeon{ namespace storages {

	class JsonFileStorage {
	public:
		JsonFileStorage(std::string filename) : filename(filename) {};
		
		template<typename T>
		inline std::shared_ptr<T> getModel() {
			static_assert(std::is_base_of<jubeon::models::ModelBase, T>::value, "");
			std::ifstream ifs(filename);
			if (!ifs.is_open()) std::cerr << "failed to open json" << std::endl;
			std::istreambuf_iterator<char> it(ifs), itEnd;
			std::shared_ptr<T> model(new T());
			model->jubeon::models::ModelBase::Init(std::string(it, itEnd));
			return model;
		};
	private:
		std::string filename;
	};
}};