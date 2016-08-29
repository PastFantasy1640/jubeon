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

		/// <summary>���O�o�͂��s��static�N���X</summary>
		class Logger {
		public:

			/// <summary>�L�^���郍�O�̃��x��</summary>
			enum LogLevel : unsigned char {
				/// <summary>���ׂẴ��O���o�͂���</summary>
				ALL,
				/// <summary>�x���A����уG���[�̃��O���o�͂���</summary>
				WARNING_AND_ERROR,
				/// <summary>�G���[�̂݃��O���o�͂���</summary>
				ERROR_ONLY
			};

			/// <summary>���O���x����ݒ肷��</summary>
			/// <param name='new_log_level'>�ݒ肷�郍�O���x��</param>
			static void setLogLevel(const LogLevel new_log_level);

			/// <summary>��񃌃x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void information(const std::string text);

			/// <summary>�x�����x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void warning(const std::string text);

			/// <summary>�G���[���x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void error(const std::string text);

			/// <summary>��O�������̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void exception(const std::string text);

			/// <summary>��񃌃x���̃��O��W���o�͂֏o�͂���</summary>
			/// <param name='new_value'>true�ŏo��</param>
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
