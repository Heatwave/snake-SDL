#include "Snake.h"
#include "utils.h"

Snake::Snake()
{
	constexpr Pos head = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	this->body.push_back(head);

	for (size_t i = 0; i < SNAKE_INIT_LENGTH; i++)
	{
		Pos pos = { this->body.back().x - SNAKE_SIZE, head.y };
		this->body.push_back(pos);
	}
}

void Snake::move()
{
	for (auto it = this->body.end() - 1; it != this->body.begin(); --it)
	{
		const Pos prev = *(it - 1);
		(*it).x = prev.x;
		(*it).y = prev.y;
	}

	const Pos headNext = this->getHeadNextPos();
	this->body.front().x = headNext.x;
	this->body.front().y = headNext.y;
}

void Snake::render(SDL_Renderer* renderer) const
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (auto it = this->body.begin(); it != this->body.end(); ++it)
	{
		SDL_Rect rect = { (*it).x, (*it).y, SNAKE_SIZE, SNAKE_SIZE };
		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Snake::checkCollision(Pos pos)
{
	for (auto it = this->body.begin(); it != this->body.end(); ++it)
	{
		if (checkPosOverlap(pos, *it) == true)
		{
			return true;
		}
	}
	return false;
}

bool Snake::checkHeadBodyCollision()
{
	const Pos head = this->getHeadPos();
	for (auto it = this->body.begin() + 1; it != this->body.end(); ++it)
	{
		if (checkPosOverlap(head, *it) == true)
		{
			return true;
		}
	}
	return false;
}

void Snake::appendHead(Pos newHeadPos)
{
	const Pos newHead = { newHeadPos.x, newHeadPos.y };
	this->body.insert(this->body.begin(), newHead);
}

Pos Snake::getHeadPos() const
{
	return this->body.front();
}

Pos Snake::getHeadNextPos() const
{
	Pos head = this->getHeadPos();

	constexpr int moveStep = SNAKE_SIZE;

	switch (this->direction)
	{
	case UP:
		head.y -= moveStep;
		break;
	case DOWN:
		head.y += moveStep;
		break;
	case LEFT:
		head.x -= moveStep;
		break;
	case RIGHT:
		head.x += moveStep;
		break;
	}

	return head;
}

Direction Snake::getDirection() const
{
	return this->direction;
}

void Snake::setDirection(const Direction dire)
{
	this->direction = dire;
}
