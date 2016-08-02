#pragma once

#ifndef jubeon_SYSTEMS_EXCEPTIONS_HPP
#define jubeon_SYSTEMS_EXCEPTIONS_HPP

#include <exception>
#include <string>

//���O�o�͂𔺂����߃��K�[�̃w�b�_
#include "Logger.hpp"

//**********************************************************
//*   std::exception�n�̌p���A�������̓I�[�o�[���C�h������
//*   ���O��Ԃ�jubeon::systems::exceptions


//��{�悭�g����O�̓��O���ꏏ�Ɏc��
namespace jubeon {
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