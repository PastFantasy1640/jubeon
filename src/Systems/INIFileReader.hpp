#pragma once

#ifndef WG_SYSTEMS_INIFILEREADER_HPP
#define WG_SYSTEMS_INIFILEREADER_HPP

#include <string>
#include <fstream>
#include <vector>

namespace wg {
	namespace systems {
		class INIFileReader {
		public:

			/// <summary>コンストラクタ</summary>
			INIFileReader(void);

			/// <summary>コピーコンストラクタ</summary>
			INIFileReader(const INIFileReader & copy);

			/// <summary>デストラクタ</summary>
			virtual ~INIFileReader(void);

			/// <summary>iniファイルをロードする</summary>
			/// <param name='filename'>ファイル名</param>
			/// <returns>成功:true   失敗:false</returns>
			bool load(const std::string filename);

			/// <summary>iniファイルの値を取得する</summary>
			/// <param name='section'>セクション</param>
			/// <param name='key'>キー</param>
			/// <param name='def_str'>デフォルト文字</param>
			/// <param name='is_existed'>指定されたキーが存在したかを格納する</param>
			/// <returns>指定されたキーの文字列を返す</returns>
			std::string get(const std::string section, const std::string key, const std::string def_str = "", bool * is_existed = nullptr) const;

			/// <summary>iniファイルの値を新しく書き換える</summary>
			/// <param name='section'>セクション</param>
			/// <param name='key'>キー</param>
			/// <param name='value'>書き込む値</param>
			bool update(const std::string section, const std::string key, std::string new_str);

			/// <summary>保持しているデータのクリア</summary>
			void clear(void);

			/// <summary>iniファイルを再読み込みする</summary>
			bool flush(void);

		private:

			struct INIFileReaderElements {
				std::string section;
				std::string key;
				std::string value;
			};

			std::vector<INIFileReaderElements> * data;

			std::fstream * file_stream;

			std::string filename;

			bool is_load_successfully;

			INIFileReaderElements _Psc(const std::string s);
			bool _ISp(const std::string s) const;
		};
	};
};


#endif	//eof WG_SYSTEMS_INIFILEREADER_HPP
