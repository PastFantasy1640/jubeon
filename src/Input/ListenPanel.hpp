/*
2015/11/28 white
�N���X�݌v�}:https://docs.google.com/drawings/d/1qoicYt3hZon5ttRrZ1ieD2bKUw4KUPVzDA_hZ18jU-0/edit

����
��̓f�o�b�O���

###############################
#ListenPanel class
###############################
#
# ������
# - <s>que_head_		: PanelEvent*
# - <s>que_num_			: unsigned int
# - <s>is_listen_		: bool
# - <s>is_overflow_		: bool
# - <s>is_tgread_exit	: std::atomic<bool>
# - <s>mtx_				: std::mutex
# - <s>panel_clock_		: sf::Clock
# - pushing_			: bool[16]
# + enum Settings : unsigned int{
#		QUEUE_MAXSIZE	= 1024
#	}
#
# + enum Result : int{
#		SUCCESS = 0,
#		INVALID_CONFIG_HID_ID = -1,
#		INVALID_CONFIG_KEYBOARD = -2,
#	}
#
#
# ������
# - <s>GetPanelThread()				: void
# - <s>SetQue(const int n)			: void
# + <s>Listen()						: int
# + <s>Close()						: void
# + <s>getEvent(PanelEvent *e, unsigned int e_num)	: unsigned int
# + <s>getEvent(std::list<PanelEvent>elist, unsigned int e_num = 0)	: unsigned int	//e_num == 0�Ȃ炠��������S��
# + <s>getQueNum()					: unsigned int
# + <s>setListenFlag(bool f)		: void
# + <s>IsOverflow()					: bool
# + <s>ResetOverflowFlag()			: bool
#####

*/


#pragma once

#ifndef JUBEAT_ONLINE_PANEL_LISTEN_H_
#define JUBEAT_ONLINE_PANEL_LISTEN_H_


#include <mutex>
#include <atomic>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

#include "PanelInput.hpp"


namespace jubeon {

	namespace input {
		
		/// <summary>�p�l���̓��͂��擾���邽�߂̃N���X</summary>
		class ListenPanel {
		public:

			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2,
			};

			enum Settings {
				QUEUE_MAXSIZE = 1024
			};

			/// <summary>���������s���֐��B���̎��ʃX���b�h���쐬����B</summary>
			/// <param name='ini_fpath'>���������邽�߂�ini�t�@�C���p�X�B</param>
			/// <returns>0:���� -1:�ُ픭��</returns>
			static int Listen(void);

			/// <summary>�I���֐�</summary>
			static void Close(void);

			/// <summary>�C�x���g��vector�^�ɂăA���L���[����B</summary>
			/// <returns>�i�[��̃��X�g��Ԃ��B</returns>
			static std::vector<PanelInput> getEvent(void);

			/// <summary>�L���[�v�f����Ԃ�</summary>
			/// <returns>�L���[�v�f��</returns>
			static size_t getQueNum(void);

			/// <summary>�L���[�������L�^���邩�ǂ����̃t���O��ݒ肷��Bfalse�ɂ����ꍇ�A���łɂ������L���[�͑S�Ĕj�������B</summary>
			/// <param name='flag'>true�Ȃ�L�^����Afalse�Ȃ痚�������������L�^���Ȃ�</param>
			static void setListenFlag(const bool flag);

			static bool IsListening(void);

			/// <summary>�I�[�o�[�t���[���Ă��邩�m�F����B</summary>
			/// <returns>�I�[�o�[�t���[�t���O</returns>
			static bool IsOverflow(void);


			/// <summary>�I�[�o�[�t���[�t���O�����Z�b�g����</summary>
			static void ResetOverflowFlag(void);

			static void setTime(const int offset);

			static sf::Clock * panel_clock_;

			static std::atomic<int> offset;
		private:
			static std::list<PanelInput> que_;

			static bool is_queue_;
			static bool is_overflow_;

			static std::atomic<bool> is_thread_exit_;


			static std::mutex mtx_;
			static void GetPanelThread(void);

			static bool pushing_[16];

			static void SetQue(const int n);


		};
	}

}


#endif