#pragma once

#ifndef JUBEON_GAME_COMBO_HPP
#define JUBEON_GAME_COMBO_HPP

namespace jubeon {
	namespace game {
		class Combo {

		private:

			unsigned int combo;

			unsigned int combo_baf;

		public:

			//コンボを1増やす。 戻り値:増やした後のコンボ数
			unsigned int increase(void);

			//コンボを絶やす（０にする）
			void reset(void);

			//現在のコンボ数を返す。 戻り値:現在のコンボ数
			unsigned int get(void) const;

			//下記メソッドclearUpdateCountが呼ばれてから値に変更があったか検知する。 戻り値:[true]変更あり。
			bool isUpdate(void) const;

			//値変更の検知フラグを伏せる。
			void clearUpdateCount(void);

			Combo();
			~Combo();
		
		};

	}
}


#endif