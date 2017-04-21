#pragma once

#ifndef JUBEON_STORAGE_JSONSTORAGE_HPP
#define JUBEON_STORAGE_JSONSTORAGE_HPP

#include "Models/wlib_Json.hpp"
#include <unordered_map>
#include <exception>
#include <memory>

namespace jubeon {
	namespace storage {

		class JsonTagDupricateException : public std::invalid_argument {
		public:
			JsonTagDupricateException(const std::string tag) throw () : std::invalid_argument("Dupricating Json Tag : " + tag) {}
			virtual ~JsonTagDupricateException() {}
		};
		
		class JsonTagNotFoundException : public std::out_of_range {
		public:
			JsonTagNotFoundException(const std::string tag) throw () : std::out_of_range("The tag is not found. [tag]" + tag) {}
			virtual ~JsonTagNotFoundException() {}
		};

		class JsonStorage {
		public:
			/** JsonStorage::store�֐�
			 * Json�N���X���^�O�t�����ĕێ����܂��B
			 * �^�O�����Ɏg���Ă���ꍇ�́A��OJsonTagDupricateException�𓊂��܂��B
			 * @param json json�N���X�̃C���X�^���X
			 * @param tag �^�O
			 * @exception JsonTagDupricateException json�̃^�O���d�����Ă���ꍇ��throw����܂��B
			 */
			static void store(const wlib::Json & json, const std::string tag) throw (JsonTagDupricateException);

			/** JsonStorage::get�֐�
			 * Json�N���X���^�O�ɂ������o���܂��B
			 * Json�N���X�̃|�C���^���Ԃ�܂��B��΂�delete�����Ȃ��ł��������B
			 * �������o�^����Ă��Ȃ��^�O���w�肳�ꂽ�ꍇ�A��OJsonTagNotFoundException�𓊂��܂��B
			 * @param tag �^�O
			 * @return �w�肳�ꂽJson�N���X�̃C���X�^���X�̃|�C���^
			 * @exception JsonTagNotFoundException �w�肳�ꂽ�^�O�����݂��Ȃ��ꍇ
			 */
			static wlib::Json * get(const std::string tag) throw (JsonTagNotFoundException);

		private:
			static std::unordered_map<std::string, std::unique_ptr<wlib::Json>> list;

		};
	}
}

#endif