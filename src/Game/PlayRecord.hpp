#pragma once

#ifndef JUBEAT_ONLINE_PLAYRECORD_HPP
#define JUBEAT_ONLINE_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "../Input/PanelEvent.hpp"
#include "JudgeDefinition.hpp"

namespace jubeat_online {
	namespace game {


		typedef struct {
			unsigned char panel_no;
			jubeat_online::input::PanelEvent::Type t;
			unsigned int ms;	//����͋ȂƓ������邪�Aoffset�����Z��̂���
			Judge j;			//�����胊�X�g�̂��̂͊֌W�Ȃ��B
		}PanelInput;


		class PlayRecord : public jubeat_online::input::PanelEvent {
		public:

			PlayRecord();
			virtual ~PlayRecord();

			//�߂�ǂ��������疢���胊�X�g��typedef����
			typedef std::unique_ptr<std::list<PanelInput>> NoJudgedList;

			//�����胊�X�g���擾
			NoJudgedList getNoJudgedList(void);

			//����ς݃��X�g��ǉ�
			void setJudgedList(NoJudgedList list);

			//�t�@�C���֏����o��
			bool writeToFile(const std::string dst);

			//�t�@�C������ǂݏo��
			bool readFromFile(const std::string src);

			//Panel�������ꂽ���̃C�x���g
			virtual void process(const unsigned char panel_no, const Type type) override;

			//�΍􂵂ĂȂ����Ǔǂݏo���݂̂Ȃ̂ŃX���b�h�Z�[�t�H
			unsigned int getTime() const;

			//judgedlist[idx]�̎擾
			const PanelInput * getJudgedInput(const size_t idx) const;

			//judgedlist�̎w�肳�ꂽms���x���A����ԋ߂����̂�const_iterator��Ԃ�
			std::vector<PanelInput>::const_iterator getPanelInputFromTime(const unsigned int ms) const;

			//judgedlist�̏I���C�e���[�^
			std::vector<PanelInput>::const_iterator getPanelInputListEnd(void) const;

			//judgedlist�̊J�n�C�e���[�^
			std::vector<PanelInput>::const_iterator getPanelInputListBegin(void) const;

		private:

			//�X���b�h�Z�[�t�΍�
			std::mutex mtx;

			//�����蕪�̃��X�g
			NoJudgedList no_judge_list;

			//����ς݂̃��X�g
			std::vector <PanelInput> judged_list;

			//����
			sf::Clock ck;
		};
	}
}

#endif