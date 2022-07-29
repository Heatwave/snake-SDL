#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "constans.h"
#include "Snake.h"

bool gameRunning = false;

int lastFrameTime = 0;

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
	gameRunning = init();

	setup();

	while (gameRunning == true)
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
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL init failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL init successed!\n");

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
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "window create successed!\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "renderer create successed!\n");

	return true;
}

void setup()
{
	lastFrameTime = SDL_GetTicks();
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			gameRunning = false;
		}

		if (event.key.keysym.sym == SDLK_DOWN)
		{
			snake.setDirection(DOWN);
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			snake.setDirection(UP);
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			snake.setDirection(LEFT);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			snake.setDirection(RIGHT);
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
	int time2wait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);

	if (time2wait > 0 && time2wait <= FRAME_TARGET_TIME)
	{
		//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "time2wait: %d\n", time2wait);
		SDL_Delay(time2wait);
	}

	float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
	//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "delta_time: %f", deltaTime);

	lastFrameTime = SDL_GetTicks();

	snake.move();
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
