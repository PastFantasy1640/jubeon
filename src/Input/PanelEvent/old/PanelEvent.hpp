/*
2015/11/16 white
�N���X�݌v�}:https://docs.google.com/drawings/d/1qoicYt3hZon5ttRrZ1ieD2bKUw4KUPVzDA_hZ18jU-0/edit

�c���Network�N���X���������Ȃ��ƍ�Ƃ��I���ł��Ȃ����߁A
����ňꎞ����

###############################
#PanelEvent class
###############################
#
# ������
# - player_id_		: unsigned int		//�v���C���[��id�BPlayer�z���id�Əƍ������Aindex�͎擾�ł���
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
# ������
# - PanelEvent()				:void
# + PanelEvent(	player_no : short,
				type : PanelEventType,
				ms : unsigned int,
				p_index : unsigned int,				//�p�l���ԍ�
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

	/// <summary>1�����̃p�l���̉����������i�[����Ă���N���X</summary>
	class PanelEvent {
	public:
		/// <summary>�p�l����Ԓ萔</summary>
		enum PanelEventType : bool {
			/// <summary>����</summary>
			PUSH = true,

			/// <summary>����</summary>
			RELEASE = false
		};

		/// <summary>�R���X�g���N�^�B���������܂�</summary>
		/// <param name='player_id'>���̗����̃v���C���[ID</param>
		/// <param name='type'>��������������</param>
		/// <param name='ms'>�C�x���g��������������ms</param>
		/// <param name='p_index'>�p�l���ԍ�</param>
		/// <param name='next_element'>���̃p�l���C�x���g�v�f</param>
		/// <param name='judge'>����i���ꂪNJ�ȊO�̏ꍇp_index��Note��ID���i�[</param>
		PanelEvent(const short player_id, const PanelEventType type, const unsigned int ms,
			const unsigned int p_index);


		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name='obj'>�R�s�[��</param>
		PanelEvent(const PanelEvent & obj);

		/// <summary>�f�X�g���N�^</summary>
		~PanelEvent(void);
		
		/// <summary>�v���C���[ID���擾����A�N�Z�T�B</summary>
		/// <returns>�v���C���[ID</returns>
		short getPlayerID(void) const;

		/// <summary>�C�x���g�^�C�v�i���������������j���擾����</summary>
		/// <returns>�C�x���g�^�C�v</returns>
		PanelEventType getEventType(void) const;

		/// <summary>�C�x���g�������������Ԃ��擾����</summary>
		/// <returns>�~���b</returns>
		unsigned int getEventTime(void) const;

		/// <summary>�p�l���ԍ����擾����B���肪NJ�ȊO�̏ꍇ��Note�̓Y���ƂȂ�B</summary>
		/// <returns>�p�l���ԍ��A��������Note�Y��</returns>
		unsigned int getPanelIndex(void) const;

		/// <summary>������ɕϊ�����</summary>
		/// <returns>������</returns>
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