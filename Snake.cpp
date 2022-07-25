#include "Snake.h"

Snake::Snake()
{
	Pos head = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	body.push_back(head);

	for (size_t i = 0; i < 5; i++)
	{
		Pos pos = { body.back().x - SNAKE_WIDTH, head.y };
		body.push_back(pos);
	}
}

void Snake::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (std::vector<Pos>::iterator it = body.begin(); it != body.end(); ++it)
	{
		SDL_Rect rect = { (*it).x, (*it).y, SNAKE_WIDTH, SNAKE_HEIGHT };
		SDL_RenderFillRect(renderer, &rect);
	}
}
