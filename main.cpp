#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "constans.h"
#include "Snake.h"

bool game_running = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Snake snake;

bool init();
void setup();
void process_input();
void update();
void render();
void close();

int main(int argc, char* args[])
{
	game_running = init();

	setup();

	while (game_running == true)
	{
		process_input();
		update();
		render();
	}

	close();

	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL init failed! Error: %s\n", SDL_GetError());
		return false;
	}

	printf("SDL init successed!\n");

	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		printf("SDL_CreateWindow failed! Error: %s\n", SDL_GetError());
		return false;
	}

	printf("window create successed!\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		printf("SDL_CreateRenderer failed! Error: %s\n", SDL_GetError());
		return false;
	}

	printf("renderer create successed!\n");

	return true;
}

void setup()
{
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		game_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			game_running = false;
		}
		break;
	case SDL_KEYUP:
		break;
	default:
		break;
	}
}

void update()
{

}

void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	snake.render(renderer);

	SDL_RenderPresent(renderer);
}

void close()
{
	SDL_Quit();
}
