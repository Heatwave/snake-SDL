#pragma once
#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

#include <SDL.h>

class Score
{
public:
	Score();

	void incrementScore();

	Uint32 getScore() const;
private:
	Uint32 score;
};

#endif // !SNAKE_SCORE_H
