#pragma once
#ifndef TARGET_H
#define TARGET

#include <SDL.h>
#include "constants.h"
#include "Snake.h"

class Target
{
public:
	Target(Snake*);

	Pos getPos() const;

	void randomPos();

	void render(SDL_Renderer*) const;
private:
	Pos pos{};
	Snake* snake;

	bool checkPosValid() const;
};

#endif // !TARGET_H
