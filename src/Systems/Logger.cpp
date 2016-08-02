#include "Logger.hpp"
#include <thread>
#include <sstream>
#include <iostream>

std::ofstream jubeon::systems::Logger::_fst;	//ファイルストリーム
std::chrono::time_point<std::chrono::system_clock> jubeon::systems::Logger::_stc = std::chrono::system_clock::now();	//現在時間
std::mutex jubeon::systems::Logger::_mtx;	//スレッドロック
bool jubeon::systems::Logger::_fir = false;	//最初のログか
#ifdef _DEBUG
jubeon::systems::Logger::LogLevel jubeon::systems::Logger::_llv = jubeon::systems::Logger::ALL;	//ログレベル(debug)
bool jubeon::systems::Logger::_sdo = true;
#else
jubeon::systems::Logger::LogLevel jubeon::systems::Logger::_llv = jubeon::systems::Logger::ERROR_ONLY;	//ログレベル(release)
bool jubeon::systems::Logger::_sdo = false;
#endif

using namespace jubeon::systems;

//絶対に実体は生成されない
jubeon::systems::Logger::Logger()
{
}

//から壊すこともできないよね
jubeon::systems::Logger::~Logger()
{
}

//ログレベルのセット
void jubeon::systems::Logger::setLogLevel(const LogLevel new_log_level)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_llv = new_log_level;
}

void jubeon::systems::Logger::_Write(const std::string text)
{
	if (text.length() > 4) {
		//形式はINFO[Th(thread_no)](current_time):hogehoge

		//もし改行文字が含まれていたらその前にtab文字を入れる
		std::stringstream textst(text);
		std::string output_text("");
		std::string buf;
		while (std::getline(textst, buf)) {
			if (output_text == "") output_text = buf;
			else output_text += "\t\t\t\t\t" + buf;
		}
		

		//スレッドのIDを取得
		std::thread::id this_id = std::this_thread::get_id();
		
		//経過時刻を取得
		auto dur = std::chrono::system_clock::now() - Logger::_stc;
		
		//ファイルオープン
		if(Logger::_fir) Logger::_fst.open("Logger.log", std::ios::app);
		else {
			Logger::_fst.open("Logger.log");
			Logger::_fir = true;
		}

		if (!Logger::_fst) {
			std::cout << "File IO Error:Can't create Logger.log" << std::endl;
			return;
		}

		Logger::_fst << text.substr(0, 4) << "[Th" << this_id << "]" << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << ":" << output_text.substr(4) << std::endl;
		Logger::_fst.close();
		if (!_fst) {
			std::cout << "File IO Error:Can't close Logger.log" << std::endl;
			return;
		}

		if (Logger::_sdo) std::cout << text.substr(0, 4) << "[Th" << this_id << "]" << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << ":" << output_text.substr(4) << std::endl;
	}
}

//情報
void jubeon::systems::Logger::information(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	//レベルのチェック
	if (Logger::_llv == Logger::LogLevel::ALL) {
		Logger::_Write("INFO" + text);
	}
}

//警告
void jubeon::systems::Logger::warning(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	//レベルチェック
	if (Logger::_llv == Logger::LogLevel::WARNING_AND_ERROR || Logger::_llv == Logger::LogLevel::ALL) {
		Logger::_Write("WARN" + text);
	}
}

//エラー
void jubeon::systems::Logger::error(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_Write("ERRO" + text);
}


//例外
void jubeon::systems::Logger::exception(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_Write("EXCP" + text);
}


void jubeon::systems::Logger::setOutputStdO(const bool new_value)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_sdo = new_value;
}
