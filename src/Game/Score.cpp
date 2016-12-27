#include "Score.hpp"

jubeon::game::Score::Score(const int notes_num) : notes_num(notes_num),score(0){

}


jubeon::game::Score::~Score(){

}


int jubeon::game::Score::getScore(void) const{
	return this->score;
}

unsigned int jubeon::game::Score::getPerfectCount(void) const{
	return this->judge_counts[PERFECT];
}

void jubeon::game::Score::incPerfectCount(void){

	this->judge_counts[PERFECT]++;
	this->calcScore();

}

unsigned int jubeon::game::Score::getGreatCount(void) const{

	return this->judge_counts[GREAT];

}

void jubeon::game::Score::incGreatCount(void){

	this->judge_counts[GREAT]++;
	this->calcScore();

}

unsigned int jubeon::game::Score::getGoodCount(void) const{

	return this->judge_counts[GOOD];

}

void jubeon::game::Score::incGoodCount(void){

	this->judge_counts[GOOD]++;
	this->calcScore();

}

unsigned int jubeon::game::Score::getEarlyCount(void) const{

	return this->judge_counts[EARLY];

}

void jubeon::game::Score::incEarlyCount(void){

	this->judge_counts[EARLY]++;
	this->calcScore();

}

unsigned int jubeon::game::Score::getLateCount(void) const{

	return this->judge_counts[LATE];

}

void jubeon::game::Score::incLateCount(void){

	this->judge_counts[LATE]++;
	this->calcScore();

}

unsigned int jubeon::game::Score::getPoorCount(void) const{

	return this->judge_counts[EARLY] + judge_counts[LATE];

}

unsigned int jubeon::game::Score::getMissCount(void) const{

	return this->judge_counts[MISS];

}

void jubeon::game::Score::incMissCount(void){

	this->judge_counts[MISS]++;
	this->calcScore();

}


void jubeon::game::Score::calcScore(void){

	this->score = (900000.0f / this->notes_num) * (this->getPerfectCount() + this->getGreatCount() * 0.7 + this->getGoodCount() * 0.4 + this->getPoorCount() * 0.1);

}


unsigned int jubeon::game::Score::getJudgeCount(const Judge & judge) const{
	return this->judge_counts.at(judge);
}


void jubeon::game::Score::incJudgeCount(const Judge & judge) const{
	this->judge_counts[judge]++;
	this->calcScore();
}
