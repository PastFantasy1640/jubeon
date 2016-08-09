//////////////////////////////////////////////////
// (c) 2016 white JudgeDefinition.hpp
//////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_GAME_JUDGEDEFINITION_HPP
#define JUBEON_GAME_JUDGEDEFINITION_HPP

#include "TypeDefinition.hpp"

//namespace is jubeon
namespace jubeon {

	typedef enum Judge : size_t {
		PERFECT = 0,
		GREAT,
		GOOD,
		EARLY,
		LATE,
		MISS,
		NOJUDGE
	} Judge;

	typedef enum JudgeSize : int{
		//|------------(B_POOR)-|JUST|-(A_POOR)----------|
		//   |---------(B_GOOD)-|JUST|-(A_GOOD)--------|
		//      |-----(B_GREAT)-|JUST|-(A_GREAT)-----|
		//		  |-(B_PERFECT)-|JUST|-(A_PERFECT)-|

		B_POOR = -500,
		B_GOOD = -350,
		B_GREAT = -120,
		B_PERFECT = -60,
		A_PERFECT = 50,
		A_GREAT = 100,
		A_GOOD = 180,
		A_POOR = 300
	}JudgeSize;

};



#endif