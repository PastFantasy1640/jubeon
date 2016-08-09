//////////////////////////////////////////////////
// (c) 2016 white JudgeDefinition.hpp
//////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_GAME_JUDGEDEFINITION_HPP
#define JUBEON_GAME_JUDGEDEFINITION_HPP

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
}

#endif