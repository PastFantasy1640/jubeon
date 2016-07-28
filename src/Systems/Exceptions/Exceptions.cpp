
#include "Exceptions.hpp"

using namespace jubeat_online::systems::exceptions;

jubeat_online::systems::exceptions::bad_alloc::bad_alloc(const std::string & msg) : ::std::bad_alloc()
{
	//ログに出力
	jubeat_online::systems::Logger::exception("(例外発生)メモリの確保に失敗しました\nmsg:" + msg + "\ne.what():" + this->what());
}