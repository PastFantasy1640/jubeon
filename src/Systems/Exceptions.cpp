
#include "Exceptions.hpp"

using namespace jubeon::systems::exceptions;

jubeon::systems::exceptions::bad_alloc::bad_alloc(const std::string & msg) : ::std::bad_alloc()
{
	//���O�ɏo��
	jubeon::systems::Logger::exception("(��O����)�������̊m�ۂɎ��s���܂���\nmsg:" + msg + "\ne.what():" + this->what());
}

jubeon::systems::exceptions::panel_out_of_index::panel_out_of_index(const std::string & msg)
{
	//���O�ɏo��
	jubeon::systems::Logger::exception("(��O����)�͈͊O�̃p�l���ԍ����w�肳��܂���\nmsg:" + msg + "\ne.what():" + this->what());
}
