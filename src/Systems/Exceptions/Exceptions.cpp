
#include "Exceptions.hpp"

using namespace jubeat_online::systems::exceptions;

jubeat_online::systems::exceptions::bad_alloc::bad_alloc(const std::string & msg) : ::std::bad_alloc()
{
	//���O�ɏo��
	jubeat_online::systems::Logger::exception("(��O����)�������̊m�ۂɎ��s���܂���\nmsg:" + msg + "\ne.what():" + this->what());
}