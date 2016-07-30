#pragma once

#ifndef JUBEAT_ONLINE_SYSTEMS_EXCEPTIONS_HPP
#define JUBEAT_ONLINE_SYSTEMS_EXCEPTIONS_HPP

#include <exception>
#include <string>

//���O�o�͂𔺂����߃��K�[�̃w�b�_
#include "../Logger/Logger.hpp"

//**********************************************************
//*   std::exception�n�̌p���A�������̓I�[�o�[���C�h������
//*   ���O��Ԃ�jubeat_online::systems::exceptions


//��{�悭�g����O�̓��O���ꏏ�Ɏc��
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