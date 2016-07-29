#pragma once

#ifndef JUBEAT_ONLINE_PLAYRECORD_HPP
#define JUBEAT_ONLINE_PLAYRECORD_HPP

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "../input/PanelEvent/PanelEvent.hpp"
#include "JudgeDefinition.hpp"

namespace jubeat_online {
	namespace game {
		class PlayRecord : public jubeat_online::input::PanelEvent {
		public:
			typedef struct {
				unsigned char panel_no;
				Type t;
				unsigned int ms;	//これは曲と同期するが、offsetを加算後のもの
				Judge j;			//未判定リストのものは関係なし。
			}PanelInput;

			PlayRecord();
			virtual ~PlayRecord();

			//めんどくさいから未判定リストはtypedefする
			typedef std::unique_ptr<std::list<PanelInput>> NoJudgedList;

			//未判定リストを取得
			NoJudgedList getNoJudgedList(void);

			//判定済みリストを追加
			void setJudgedList(NoJudgedList list);

			//ファイルへ書き出し
			bool writeToFile(const std::string dst);

			//ファイルから読み出し
			bool readFromFile(const std::string src);

			//Panelが押された時のイベント
			virtual void process(const unsigned char panel_no, const Type type) override;

			//対策してないけど読み出しのみなのでスレッドセーフ？
			unsigned int getTime() const;

			//judgedlist[idx]の取得
			const PanelInput * getJudgedInput(const size_t idx) const;

			//judgedlistの指定されたmsより遅く、かつ一番近いもののconst_iteratorを返す
			std::vector<PanelInput>::const_iterator getPanelInputFromTime(const unsigned int ms) const;

			//judgedlistの終了イテレータ
			std::vector<PanelInput>::const_iterator getPanelInputListEnd(void) const;

		private:

			//スレッドセーフ対策
			std::mutex mtx;

			//未判定分のリスト
			NoJudgedList no_judge_list;

			//判定済みのリスト
			std::vector <PanelInput> judged_list;

			//時間
			sf::Clock ck;
		};
	}
}

#endif