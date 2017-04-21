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
			/** JsonStorage::store関数
			 * Jsonクラスをタグ付けして保持します。
			 * タグが既に使われている場合は、例外JsonTagDupricateExceptionを投げます。
			 * @param json jsonクラスのインスタンス
			 * @param tag タグ
			 * @exception JsonTagDupricateException jsonのタグが重複している場合にthrowされます。
			 */
			static void store(const wlib::Json & json, const std::string tag) throw (JsonTagDupricateException);

			/** JsonStorage::get関数
			 * Jsonクラスをタグにより引き出します。
			 * Jsonクラスのポインタが返ります。絶対にdeleteをしないでください。
			 * もしも登録されていないタグが指定された場合、例外JsonTagNotFoundExceptionを投げます。
			 * @param tag タグ
			 * @return 指定されたJsonクラスのインスタンスのポインタ
			 * @exception JsonTagNotFoundException 指定されたタグが存在しない場合
			 */
			static wlib::Json * get(const std::string tag) throw (JsonTagNotFoundException);

		private:
			static std::unordered_map<std::string, std::unique_ptr<wlib::Json>> list;

		};
	}
}

#endif