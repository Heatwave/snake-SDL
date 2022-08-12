#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdio>
#include "constants.h"
#include "Snake.h"
#include "Target.h"
#include "utils.h"
#include "Score.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

bool init();
void gameLoop();
void setup(Uint32&);
bool waitingGameStartInput();
void processInput(Snake&, bool&);
void update(Snake&, Target&, Score&, Uint32&);
bool check(Snake&, bool&);
void render(const Snake&, const Target&);
void close();

int main(int argc, char* args[])
{
	if (init() == false)
	{
		close();
		return -1;
	}

	while (true)
	{
		showMessage("Press any key to start", true, renderer, font);
		if (waitingGameStartInput() == true)
		{
			gameLoop();
		}
		else
		{
			break;
		}
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

	SDL_Log("SDL init succeeded!\n");

	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Log("window create succeeded!\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Log("renderer create succeeded!\n");

	if (TTF_Init() != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed! Error: %s\n", SDL_GetError());
		return false;
	}

	font = TTF_OpenFont(FONT_FILE_NAME, FONT_SIZE_PT);
	if (font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load %d pt font from %s: %s\n",
			FONT_SIZE_PT, FONT_FILE_NAME, SDL_GetError());
		return false;
	}

	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	TTF_SetFontOutline(font, 0);
	TTF_SetFontKerning(font, 1);
	TTF_SetFontHinting(font, TTF_HINTING_NORMAL);

	return true;
}

bool waitingGameStartInput()
{
	SDL_PumpEvents();
	SDL_FlushEvent(SDL_KEYDOWN);

	SDL_Event event;

	while (true)
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return false;
			}
			return true;
		default:
			break;
		}

		SDL_Delay(100);
	}
}

void gameLoop()
{
	Snake snake;
	Target target(&snake);
	Score score;

	bool gameRunning = true;
	Uint32 lastFrameTime = 0;
	bool lose = false;

	setup(lastFrameTime);

	while (gameRunning == true)
	{
		processInput(snake, gameRunning);
		update(snake, target, score, lastFrameTime);
		lose = check(snake, gameRunning);
		render(snake, target);
	}

	if (lose == true)
	{
		char str[50];
		snprintf(str, 50, "Your score: %d", score.getScore());
		showMessage(str, false, renderer, font);
		SDL_Delay(3000);
	}
}

void setup(Uint32& lastFrameTime)
{
	lastFrameTime = SDL_GetTicks();
}

void processInput(Snake& snake, bool& gameRunning)
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

		if (event.key.keysym.sym == SDLK_DOWN && snake.getDirection() != UP)
		{
			snake.setDirection(DOWN);
		}
		else if (event.key.keysym.sym == SDLK_UP && snake.getDirection() != DOWN)
		{
			snake.setDirection(UP);
		}
		else if (event.key.keysym.sym == SDLK_LEFT && snake.getDirection() != RIGHT)
		{
			snake.setDirection(LEFT);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && snake.getDirection() != LEFT)
		{
			snake.setDirection(RIGHT);
		}
		break;
	default:
		break;
	}
}

void update(Snake& snake, Target& target, Score& score, Uint32& lastFrameTime)
{
	const int time2wait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);

	if (time2wait > 0 && time2wait <= FRAME_TARGET_TIME)
	{
		//SDL_Log("time2wait: %d\n", time2wait);
		SDL_Delay(time2wait);
	}

	// float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
	//SDL_Log("delta_time: %f", deltaTime);

	lastFrameTime = SDL_GetTicks();

	if (checkPosOverlap(snake.getHeadNextPos(), target.getPos()) == true)
	{
		snake.appendHead(target.getPos());
		target.randomPos();
		score.incrementScore();
	}
	else
	{
		snake.move();
	}
}

bool check(Snake& snake, bool& gameRunning)
{
	const Pos head = snake.getHeadPos();

	if (head.x >= WINDOW_WIDTH ||
		head.x <= 0 ||
		head.y >= WINDOW_HEIGHT ||
		head.y <= 0)
	{
		gameRunning = false;
		return true;
	}

	if (snake.checkHeadBodyCollision() == true)
	{
		gameRunning = false;
		return true;
	}

	return false;
}

void render(const Snake& snake, const Target& target)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	snake.render(renderer);
	target.render(renderer);

	SDL_RenderPresent(renderer);
}

void close()
{
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
