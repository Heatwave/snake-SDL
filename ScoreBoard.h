#pragma once
#ifndef SNAKE_SCORE_BOARD_H
#define SNAKE_SCORE_BOARD_H

#include <SDL.h>
#include <map>
#include <set>
#include <string>

#include "constants.h"
#include "utils.h"

class ScoreBoard
{
public:
	ScoreBoard();
	~ScoreBoard();

	void render(SDL_Renderer*, TTF_Font*, std::set<std::pair<std::string, size_t>, classcomp>&) const;
};


#endif // !SNAKE_SCORE_BOARD_H
