#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include "constans.h"

#define SNAKE_WIDTH 10
#define SNAKE_HEIGHT 10

#define SNAKE_SIZE 10

#define SNAKE_INIT_LENGTH 5

#define SNAKE_VELOCITY 200

class Snake
{
public:
	Snake();

	void move();

	void render(SDL_Renderer*);

	void setDirection(Direction);
private:
	std::vector<Pos> body;
	Direction direction = RIGHT;
};

#endif // !SNAKE_H
