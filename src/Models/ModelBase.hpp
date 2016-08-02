#pragma once

#include <string>
#include "Systems/picojson.hpp"

namespace jubeat_online { namespace models {
	class ModelBase {
	public:
		inline bool Init(std::string jsonStr) {
			picojson::value v;
			std::string err = picojson::parse(v, jsonStr);
			if (!err.empty()) {
				return false;
			}
			return this->Init(v);
		};
		virtual bool Init(picojson::value val) = 0;
		virtual picojson::value GetJsonValue() = 0;
		inline std::string ToString() {
			return this->GetJsonValue().serialize();
		};
	};
}};