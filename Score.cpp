#include "Score.h"

Score::Score()
{
	this->score = 0;
}


void Score::incrementScore()
{
	this->score++;
}

Uint32 Score::getScore() const
{
	return this->score;
}
