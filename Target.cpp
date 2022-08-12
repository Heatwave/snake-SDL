#include "Target.h"
#include "utils.h"

Target::Target(Snake* snake)
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->snake = snake;
	randomPos();
}

Pos Target::getPos() const
{
	return this->pos;
}

void Target::randomPos()
{
	this->pos.x = floorInt(rand() % WINDOW_WIDTH, SNAKE_SIZE);
	this->pos.y = floorInt(rand() % WINDOW_HEIGHT, SNAKE_SIZE);
	if (this->checkPosValid() == false)
	{
		this->randomPos();
	}
}

bool Target::checkPosValid() const
{
	if (this->pos.x == 0 || this->pos.x >= WINDOW_WIDTH)
	{
		return false;
	}
	if (this->pos.y == 0 || this->pos.y >= WINDOW_HEIGHT)
	{
		return false;
	}
	if (this->snake->checkCollision(this->pos) == true)
	{
		return false;
	}
	return true;
}

void Target::render(SDL_Renderer* renderer) const
{

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	const SDL_Rect rect = { this->pos.x, this->pos.y, SNAKE_SIZE, SNAKE_SIZE };
	SDL_RenderFillRect(renderer, &rect);
}
