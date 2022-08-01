#include "Snake.h"

Snake::Snake()
{
	Pos head = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	this->body.push_back(head);

	for (size_t i = 0; i < SNAKE_INIT_LENGTH; i++)
	{
		Pos pos = { this->body.back().x - SNAKE_SIZE, head.y };
		this->body.push_back(pos);
	}
}

void Snake::move()
{
	for (std::vector<Pos>::iterator it = this->body.end() - 1; it != this->body.begin(); --it)
	{
		Pos prev = *(it - 1);
		(*it).x = prev.x;
		(*it).y = prev.y;
	}

	int moveStep = SNAKE_SIZE;

	switch (this->direction)
	{
	case UP:
		this->body.front().y -= moveStep;
		break;
	case DOWN:
		this->body.front().y += moveStep;
		break;
	case LEFT:
		this->body.front().x -= moveStep;
		break;
	case RIGHT:
		this->body.front().x += moveStep;
		break;
	default:
		break;
	}
}

void Snake::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (std::vector<Pos>::iterator it = this->body.begin(); it != this->body.end(); ++it)
	{
		SDL_Rect rect = { (*it).x, (*it).y, SNAKE_SIZE, SNAKE_SIZE };
		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Snake::checkHeadBodyCollision()
{
	Pos head = this->getHeadPos();
	for (std::vector<Pos>::iterator it = this->body.begin() + 1; it != this->body.end(); ++it)
	{
		if (checkPosOverlap(head, *it) == true)
		{
			return true;
		}
	}
	return false;
}

Pos Snake::getHeadPos()
{
	return this->body.front();
}

Direction Snake::getDirection()
{
	return this->direction;
}

void Snake::setDirection(Direction direction)
{
	this->direction = direction;
}
