#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include "constans.h"

#define SNAKE_WIDTH 10
#define SNAKE_HEIGHT 10

class Snake
{
public:
	Snake();

	void render(SDL_Renderer* renderer);
private:
	std::vector<Pos> body;
};

#endif // !SNAKE_H
