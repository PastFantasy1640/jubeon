#pragma once

#ifndef jubeon_SYSTEMS_LOGGER_HPP
#define jubeon_SYSTEMS_LOGGER_HPP
//#define _DEBUG
#include <fstream>
#include <chrono>
#include <mutex>

#define jubeon_SYSTEM_LOGGER_DEFAULT_PATH "Logger.ini"

namespace jubeon {
	namespace systems {

		/// <summary>ログ出力を行うstaticクラス</summary>
		class Logger {
		public:

			/// <summary>記録するログのレベル</summary>
			enum LogLevel : unsigned char {
				/// <summary>すべてのログを出力する</summary>
				ALL,
				/// <summary>警告、およびエラーのログを出力する</summary>
				WARNING_AND_ERROR,
				/// <summary>エラーのみログを出力する</summary>
				ERROR_ONLY
			};

			/// <summary>ログレベルを設定する</summary>
			/// <param name='new_log_level'>設定するログレベル</param>
			static void setLogLevel(const LogLevel new_log_level);

			/// <summary>情報レベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void information(const std::string text);

			/// <summary>警告レベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void warning(const std::string text);

			/// <summary>エラーレベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void error(const std::string text);

			/// <summary>例外発生時のログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void exception(const std::string text);

			/// <summary>情報レベルのログを標準出力へ出力する</summary>
			/// <param name='new_value'>trueで出力</param>
			static void setOutputStdO(const bool new_value);

		private:
			static std::ofstream _fst;
			static LogLevel _llv;
			static std::mutex _mtx;
			static std::chrono::time_point<std::chrono::system_clock> _stc;
			static bool _sdo;
			static bool _fir;
			Logger();
			~Logger();
			static void _Write(const std::string text);
		};	
	};
};

#endif
