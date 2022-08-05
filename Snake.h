#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include "constans.h"
#include "utils.h"

#define SNAKE_WIDTH 10
#define SNAKE_HEIGHT 10

#define SNAKE_SIZE 10

#define SNAKE_INIT_LENGTH 20

#define SNAKE_VELOCITY 200

class Snake
{
public:
	Snake();

	void move();

	void render(SDL_Renderer*);

	bool checkCollision(Pos pos);

	bool checkHeadBodyCollision();

	Pos getHeadPos();

	Direction getDirection();

	void setDirection(Direction);
private:
	std::vector<Pos> body;
	Direction direction = RIGHT;
};

#endif // !SNAKE_H
