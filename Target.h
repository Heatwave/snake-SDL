#pragma once
#ifndef TARGET_H
#define TARGET

#include <SDL.h>
#include "constans.h"
#include "utils.h"
#include "Snake.h"

class Target
{
public:
	Target(Snake*);

	Pos getPos();

	void randomPos();

	void render(SDL_Renderer*);
private:
	Pos pos;
	Snake* snake;

	bool checkPosValid();
};

#endif // !TARGET_H
