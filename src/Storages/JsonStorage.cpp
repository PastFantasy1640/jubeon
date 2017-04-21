#include "JsonStorage.hpp"

std::unordered_map<std::string, std::unique_ptr<wlib::Json>> jubeon::storage::JsonStorage::list;

void jubeon::storage::JsonStorage::store(const wlib::Json & json, const std::string tag) throw(JsonTagDupricateException)
{
	//�^�O���d�����Ă��Ȃ���
	if (JsonStorage::list.count(tag)) throw JsonTagDupricateException(tag);

	//�o�^����
	JsonStorage::list.at(tag).reset(new wlib::Json(json));
}

wlib::Json * jubeon::storage::JsonStorage::get(const std::string tag) throw(JsonTagNotFoundException)
{
	try{
		//�擾���ă|�C���^��Ԃ��B
		return JsonStorage::list.at(tag).get();
	}
	catch (std::out_of_range &) {
		//�^�O�����݂��Ȃ������ꍇ
		throw JsonTagNotFoundException(tag);
	}
	return nullptr;
}

