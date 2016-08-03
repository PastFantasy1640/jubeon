#pragma once
#include <string>
#include <memory>
#include <type_traits>
#include <fstream>
#include "Models/ModelBase.hpp"

namespace jubeat_online { namespace storages {

	class JsonFileStorage {
	public:
		JsonFileStorage(std::string filename) : filename(filename) {};
		
		template<typename T>
		inline std::shared_ptr<T> getModel() {
			static_assert(std::is_base_of<jubeat_online::models::ModelBase, T>::value, "");
			std::ifstream ifs(filename);
			std::istreambuf_iterator<char> it(ifs), itEnd;
			std::shared_ptr<T> model(new T());
			model->jubeat_online::models::ModelBase::Init(std::string(it, itEnd));
			return model;
		};
	private:
		std::string filename;
	};
}};