#include "Score.hpp"

jubeon::game::Score::Score(const int notes_num) 
	: notes_num(notes_num),score(0),before_score(0),
	judge_counts{ 0,0,0,0,0,0 } {

}


jubeon::game::Score::~Score(){

}


unsigned int jubeon::game::Score::getScore(void) const{
	return this->score;
}

unsigned int jubeon::game::Score::getAnimatedScore(void) const
{
	if (this->score_clock.getElapsedTime().asMilliseconds() < this->SCORE_INCRESE_SPEED_MS) {
		return this->before_score + static_cast<unsigned int>(this->diff_score * this->score_clock.getElapsedTime().asMilliseconds() / 500.0f);
	}
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

	
	this->before_score = this->getAnimatedScore();
		
	double score2 = 900000.0f * (static_cast<double>(this->getPerfectCount()) + static_cast<double>(this->getGreatCount()) * 0.7f + static_cast<double>(this->getGoodCount()) * 0.4f + static_cast<double>(this->getPoorCount()) * 0.1f) / static_cast<double>(this->notes_num);
	
	this->score = static_cast<double>(score2);

	//‚Ð‚Á‚­‚è•Ô‚ç‚È‚¢‚æ‚¤‚É
	if (this->score > this->before_score)	this->diff_score = this->score - this->before_score;

	this->score_clock.restart();
}


unsigned int jubeon::game::Score::getJudgeCount(const Judge & judge) const{
	return this->judge_counts.at(judge);
}

#include <iostream>

void jubeon::game::Score::incJudgeCount(const Judge & judge) {
	this->judge_counts[judge]++;
	this->calcScore();
	std::cout << "Score:" << this->getScore() << std::endl;
}
