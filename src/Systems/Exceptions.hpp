#pragma once

#ifndef JUBEAT_ONLINE_SYSTEMS_EXCEPTIONS_HPP
#define JUBEAT_ONLINE_SYSTEMS_EXCEPTIONS_HPP

#include <exception>
#include <string>

//ログ出力を伴うためロガーのヘッダ
#include "../Logger/Logger.hpp"

//**********************************************************
//*   std::exception系の継承、もしくはオーバーライドをする
//*   名前空間はjubeat_online::systems::exceptions


//基本よく使う例外はログを一緒に残す
namespace jubeat_online {
	namespace systems {
		namespace exceptions {
			class bad_alloc : ::std::bad_alloc {
			public:
				bad_alloc(const std::string & msg);
			};


			class panel_out_of_index : ::std::exception {
			public:
				panel_out_of_index(const std::string & msg);
			};
		}	
	}
}

#endif