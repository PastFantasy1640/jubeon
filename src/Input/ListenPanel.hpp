/*
2015/11/28 white
クラス設計図:https://docs.google.com/drawings/d/1qoicYt3hZon5ttRrZ1ieD2bKUw4KUPVzDA_hZ18jU-0/edit

完成
後はデバッグ作業

###############################
#ListenPanel class
###############################
#
# ●属性
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
# ●操作
# - <s>GetPanelThread()				: void
# - <s>SetQue(const int n)			: void
# + <s>Listen()						: int
# + <s>Close()						: void
# + <s>getEvent(PanelEvent *e, unsigned int e_num)	: unsigned int
# + <s>getEvent(std::list<PanelEvent>elist, unsigned int e_num = 0)	: unsigned int	//e_num == 0ならありったけ全部
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
		
		/// <summary>パネルの入力を取得するためのクラス</summary>
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

			/// <summary>初期化を行う関数。この時別スレッドを作成する。</summary>
			/// <param name='ini_fpath'>初期化するためのiniファイルパス。</param>
			/// <returns>0:成功 -1:異常発生</returns>
			static int Listen(void);

			/// <summary>終了関数</summary>
			static void Close(void);

			/// <summary>イベントをvector型にてアンキューする。</summary>
			/// <returns>格納後のリストを返す。</returns>
			static std::vector<PanelInput> getEvent(void);

			/// <summary>キュー要素数を返す</summary>
			/// <returns>キュー要素数</returns>
			static size_t getQueNum(void);

			/// <summary>キュー履歴を記録するかどうかのフラグを設定する。falseにした場合、すでにあったキューは全て破棄される。</summary>
			/// <param name='flag'>trueなら記録する、falseなら履歴を初期化し記録しない</param>
			static void setListenFlag(const bool flag);

			static bool IsListening(void);

			/// <summary>オーバーフローしているか確認する。</summary>
			/// <returns>オーバーフローフラグ</returns>
			static bool IsOverflow(void);


			/// <summary>オーバーフローフラグをリセットする</summary>
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