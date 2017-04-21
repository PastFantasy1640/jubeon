#include "JsonStorage.hpp"

std::unordered_map<std::string, std::unique_ptr<wlib::Json>> jubeon::storage::JsonStorage::list;

void jubeon::storage::JsonStorage::store(const wlib::Json & json, const std::string tag) throw(JsonTagDupricateException)
{
	//タグが重複していないか
	if (JsonStorage::list.count(tag)) throw JsonTagDupricateException(tag);

	//登録する
	JsonStorage::list.at(tag).reset(new wlib::Json(json));
}

wlib::Json * jubeon::storage::JsonStorage::get(const std::string tag) throw(JsonTagNotFoundException)
{
	try{
		//取得してポインタを返す。
		return JsonStorage::list.at(tag).get();
	}
	catch (std::out_of_range &) {
		//タグが存在しなかった場合
		throw JsonTagNotFoundException(tag);
	}
	return nullptr;
}

