#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include "constants.h"

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

	void render(SDL_Renderer*) const;

	bool checkCollision(Pos);

	bool checkHeadBodyCollision();

	void appendHead(Pos);

	Pos getHeadPos() const;

	Pos getHeadNextPos() const;

	Direction getDirection() const;

	void setDirection(Direction);
private:
	std::vector<Pos> body;
	Direction direction = RIGHT;
};

#endif // !SNAKE_H
