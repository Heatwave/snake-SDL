#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "constans.h"
#include "Snake.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

bool init();
void gameLoop();
void setup(Uint32&);
bool waitingGameStartInput();
void processInput(Snake&, bool&);
void update(Snake&, Uint32&);
void check(Snake&, bool&);
void render(Snake&);
void close();

int main(int argc, char* args[])
{
	if (init() == false)
	{
		close();
		return -1;
	}

	SDL_Texture* message;
	SDL_Rect messageRect;

	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };

	SDL_Surface* text = TTF_RenderUTF8_Solid(font, "Press any key to start", white);

	messageRect.x = (WINDOW_WIDTH - text->w) / 2;
	messageRect.y = (WINDOW_HEIGHT - text->h) / 2;
	messageRect.w = text->w;
	messageRect.h = text->h;
	message = SDL_CreateTextureFromSurface(renderer, text);

	while (true)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, message, NULL, &messageRect);
		SDL_RenderPresent(renderer);

		bool startGame = waitingGameStartInput();
		if (startGame == true)
		{
			gameLoop();
		}
		else
		{
			break;
		}
	}

	SDL_FreeSurface(text);
	SDL_DestroyTexture(message);

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

	SDL_Log("SDL init successed!\n");

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

	SDL_Log("window create successed!\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed! Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Log("renderer create successed!\n");

	if (TTF_Init() != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed! Error: %s\n", SDL_GetError());
		return false;
	}

	font = TTF_OpenFont(FONT_FILE_NAME, FONT_SIZE_PT);
	if (font == NULL)
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
	bool gameRunning = true;
	Uint32 lastFrameTime = 0;

	setup(lastFrameTime);

	while (gameRunning == true)
	{
		processInput(snake, gameRunning);
		update(snake, lastFrameTime);
		check(snake, gameRunning);
		render(snake);
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

void update(Snake& snake, Uint32& lastFrameTime)
{
	int time2wait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);

	if (time2wait > 0 && time2wait <= FRAME_TARGET_TIME)
	{
		//SDL_Log("time2wait: %d\n", time2wait);
		SDL_Delay(time2wait);
	}

	float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
	//SDL_Log("delta_time: %f", deltaTime);

	lastFrameTime = SDL_GetTicks();

	snake.move();
}

void check(Snake& snake, bool& gameRunning)
{
	Pos head = snake.getHeadPos();

	if (head.x >= WINDOW_WIDTH ||
		head.x <= 0 ||
		head.y >= WINDOW_HEIGHT ||
		head.y <= 0)
	{
		gameRunning = false;
	}
}

void render(Snake& snake)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	snake.render(renderer);

	SDL_RenderPresent(renderer);
}

void close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
