#pragma once
#include <string>
#include <memory>
#include <type_traits>
#include <fstream>

namespace jubeat_online { namespace storages {

	class JsonFileStorage {
	public:
		JsonFileStorage(std::string filename) : filename(filename) {};
		
		template<T>
		inline std::shared_ptr<T> getModel() {
			std::ifstream ifs(filename);
			std::istreambuf_iterator<char> it(ifs), itEnd;
			std::shared_ptr model(new T());
			model->Init(std::string(it, itEnd));
			return model;
		};
	private:
		std::string filename;
	};
}};