#pragma once
#ifndef SNAKE_SCORE_BOARD_H
#define SNAKE_SCORE_BOARD_H

#include <SDL.h>
#include <map>
#include <set>
#include <string>

#include "constants.h"
#include "utils.h"

struct classcomp {
	bool operator() (const std::pair<std::string, size_t>& lhs, const std::pair<std::string, size_t>& rhs) const
	{
		return lhs.second > rhs.second;
	}
};

class ScoreBoard
{
public:
	ScoreBoard();
	~ScoreBoard();

	void readFileToScores(const char*);

	void render(SDL_Renderer*, TTF_Font*) const;

private:
	std::set<std::pair<std::string, size_t>, classcomp> scores;
};


#endif // !SNAKE_SCORE_BOARD_H
