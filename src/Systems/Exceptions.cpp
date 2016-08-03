
#include "Exceptions.hpp"

using namespace jubeon::systems::exceptions;

jubeon::systems::exceptions::bad_alloc::bad_alloc(const std::string & msg) : ::std::bad_alloc()
{
	//ログに出力
	jubeon::systems::Logger::exception("(例外発生)メモリの確保に失敗しました\nmsg:" + msg + "\ne.what():" + this->what());
}

jubeon::systems::exceptions::panel_out_of_index::panel_out_of_index(const std::string & msg)
{
	//ログに出力
	jubeon::systems::Logger::exception("(例外発生)範囲外のパネル番号が指定されました\nmsg:" + msg + "\ne.what():" + this->what());
}
