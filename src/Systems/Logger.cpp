#include "Logger.hpp"
#include <thread>
#include <sstream>
#include <iostream>

std::ofstream jubeat_online::systems::Logger::_fst;	//�t�@�C���X�g���[��
std::chrono::time_point<std::chrono::system_clock> jubeat_online::systems::Logger::_stc = std::chrono::system_clock::now();	//���ݎ���
std::mutex jubeat_online::systems::Logger::_mtx;	//�X���b�h���b�N
bool jubeat_online::systems::Logger::_fir = false;	//�ŏ��̃��O��
#ifdef _DEBUG
jubeat_online::systems::Logger::LogLevel jubeat_online::systems::Logger::_llv = jubeat_online::systems::Logger::ALL;	//���O���x��(debug)
bool jubeat_online::systems::Logger::_sdo = true;
#else
jubeat_online::systems::Logger::LogLevel jubeat_online::systems::Logger::_llv = jubeat_online::systems::Logger::ERROR_ONLY;	//���O���x��(release)
bool jubeat_online::systems::Logger::_sdo = false;
#endif

using namespace jubeat_online::systems;

//��΂Ɏ��̂͐�������Ȃ�
jubeat_online::systems::Logger::Logger()
{
}

//����󂷂��Ƃ��ł��Ȃ����
jubeat_online::systems::Logger::~Logger()
{
}

//���O���x���̃Z�b�g
void jubeat_online::systems::Logger::setLogLevel(const LogLevel new_log_level)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_llv = new_log_level;
}

void jubeat_online::systems::Logger::_Write(const std::string text)
{
	if (text.length() > 4) {
		//�`����INFO[Th(thread_no)](current_time):hogehoge

		//�������s�������܂܂�Ă����炻�̑O��tab����������
		std::stringstream textst(text);
		std::string output_text("");
		std::string buf;
		while (std::getline(textst, buf)) {
			if (output_text == "") output_text = buf;
			else output_text += "\t\t\t\t\t" + buf;
		}
		

		//�X���b�h��ID���擾
		std::thread::id this_id = std::this_thread::get_id();
		
		//�o�ߎ������擾
		auto dur = std::chrono::system_clock::now() - Logger::_stc;
		
		//�t�@�C���I�[�v��
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

//���
void jubeat_online::systems::Logger::information(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	//���x���̃`�F�b�N
	if (Logger::_llv == Logger::LogLevel::ALL) {
		Logger::_Write("INFO" + text);
	}
}

//�x��
void jubeat_online::systems::Logger::warning(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	//���x���`�F�b�N
	if (Logger::_llv == Logger::LogLevel::WARNING_AND_ERROR || Logger::_llv == Logger::LogLevel::ALL) {
		Logger::_Write("WARN" + text);
	}
}

//�G���[
void jubeat_online::systems::Logger::error(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_Write("ERRO" + text);
}


//��O
void jubeat_online::systems::Logger::exception(const std::string text)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_Write("EXCP" + text);
}


void jubeat_online::systems::Logger::setOutputStdO(const bool new_value)
{
	std::lock_guard<std::mutex> lock(Logger::_mtx);
	Logger::_sdo = new_value;
}
