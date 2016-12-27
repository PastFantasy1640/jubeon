///////////////////////////////////////////////////////
// (c) 2016  Retasu
///////////////////////////////////////////////////////


#pragma once

//include guard
#ifndef JUBEON_GAME_SCORE_HPP
#define JUBEON_GAME_SCORE_HPP

//for array
#include <array>

//for notes definition
#include "Game/JudgeDefinition.hpp"

namespace jubeon{
	namespace game{
		class Score{
		
		public:
			
			/** Constructor with args.
			 * @param note_num notes size
			 */
			Score(const int notes_num);
			
			/** Destructor
			 */
			virtual ~Score();

			/** Get the score.
			 * @returns current score
			 */
			int getScore(void) const;

			unsigned int getPerfectCount(void) const;
			void incPerfectCount(void);

			unsigned int getGreatCount(void) const;
			void incGreatCount(void);

			unsigned int getGoodCount(void) const;
			void incGoodCount(void);

			unsigned int getEarlyCount(void) const;
			void incEarlyCount(void);

			unsigned int getLateCount(void) const;
			void incLateCount(void);

			unsigned int getPoorCount(void) const;
			void incPoorCount(void);

			unsigned int getMissCount(void) const;
			void incMissCount(void);
			
			unsigned int getJudgeCount(const Judge & judge) const;
			void incJudgeCount(const Judge & judge) ;

		private:
			//Constructor [forbidden]
			Score();
			
			//////////////////////
			// Member variables
			//////////////////////
			unsigned int score;
			std::array < unsigned int, 6 > judge_counts;
			unsigned int notes_num;

			//Internal Function.
			//Score update
			void calcScore(void);
		};
	};
};

#endif

