#include "Systems/picojson.hpp"

namespace picojson_util {
	template<typename T>
	inline bool has_field(picojson::value val, std::string key) {
		picojson::object root = val.get<picojson::object>(val);
		return (root.find(key) != root.end() && root[key].is<T>());
	};
};