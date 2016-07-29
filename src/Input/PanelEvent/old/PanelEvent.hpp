/*
2015/11/16 white
クラス設計図:https://docs.google.com/drawings/d/1qoicYt3hZon5ttRrZ1ieD2bKUw4KUPVzDA_hZ18jU-0/edit

残りはNetworkクラスが完成しないと作業を終了できないため、
これで一時完成

###############################
#PanelEvent class
###############################
#
# ●属性
# - player_id_		: unsigned int		//プレイヤーのid。Player配列のidと照合させ、indexは取得できる
# - type_			: PanelEventType	//
# - judge_			: JudgeType
# - ms_				: unsigned int
# - panel_index_	: unsigned int
# + next_elements_	: PanelEvent *
#
# + PanelEventType enum{
#		PUSH
#		RELEASE
#	}
#
# ●操作
# - PanelEvent()				:void
# + PanelEvent(	player_no : short,
				type : PanelEventType,
				ms : unsigned int,
				p_index : unsigned int,				//パネル番号
				next_elements = NULL : PanelEvent*,
				Judge judge = NL : Judge )	:void
# + getPlayerID()				: unsigned int
# + getEventType()				: PanelEvent
# + getEventTime()				: unsigned int
# + getPanelIndex()				: unsigned int
# + <s>Parse(NetworkData)		: PanelEvent
# + ~PanelEvent()				: void
#####

*/


#pragma once
#ifndef JUBEAT_ONLINE_PANEL_EVENT_H_
#define JUBEAT_ONLINE_PANEL_EVENT_H_



#include <string>

namespace jubeat_online {

	/// <summary>1件分のパネルの押下履歴が格納されているクラス</summary>
	class PanelEvent {
	public:
		/// <summary>パネル状態定数</summary>
		enum PanelEventType : bool {
			/// <summary>押下</summary>
			PUSH = true,

			/// <summary>離す</summary>
			RELEASE = false
		};

		/// <summary>コンストラクタ。初期化します</summary>
		/// <param name='player_id'>その履歴のプレイヤーID</param>
		/// <param name='type'>押下か離したか</param>
		/// <param name='ms'>イベントが発生した時のms</param>
		/// <param name='p_index'>パネル番号</param>
		/// <param name='next_element'>次のパネルイベント要素</param>
		/// <param name='judge'>判定（これがNJ以外の場合p_indexはNoteのIDを格納</param>
		PanelEvent(const short player_id, const PanelEventType type, const unsigned int ms,
			const unsigned int p_index);


		/// <summary>コピーコンストラクタ</summary>
		/// <param name='obj'>コピー元</param>
		PanelEvent(const PanelEvent & obj);

		/// <summary>デストラクタ</summary>
		~PanelEvent(void);
		
		/// <summary>プレイヤーIDを取得するアクセサ。</summary>
		/// <returns>プレイヤーID</returns>
		short getPlayerID(void) const;

		/// <summary>イベントタイプ（押下か離したか）を取得する</summary>
		/// <returns>イベントタイプ</returns>
		PanelEventType getEventType(void) const;

		/// <summary>イベントが発生した時間を取得する</summary>
		/// <returns>ミリ秒</returns>
		unsigned int getEventTime(void) const;

		/// <summary>パネル番号を取得する。判定がNJ以外の場合はNoteの添字となる。</summary>
		/// <returns>パネル番号、もしくはNote添字</returns>
		unsigned int getPanelIndex(void) const;

		/// <summary>文字列に変換する</summary>
		/// <returns>文字列</returns>
		std::string ToString(void) const;


	private:

		PanelEvent();
		short player_id_;
		PanelEventType type_;
		unsigned int ms_;
		unsigned int panel_index_;

	};


	

}


#endif