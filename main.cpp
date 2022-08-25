#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdio>
#include "constants.h"
#include "Snake.h"
#include "Target.h"
#include "utils.h"
#include "Score.h"
#include "Menu.h"
#include "NameBoard.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

bool init();
void setup(Uint32&);
void waitingMenuSelection(Menu&);
Uint32 gameLoop(GameState&);
void processInput(Snake&, GameState&);
void update(Snake&, Target&, Score&, Uint32&);
bool check(Snake&);
void render(const Snake&, const Target&);
void saveScore(Uint32);
bool isConfirmed(NameBoard&);
void close();

int main(int argc, char* args[])
{
	if (init() == false)
	{
		close();
		return -1;
	}

	GameState gameState = GAME_STATE_RUNNING;

	while (gameState != GAME_STATE_EXITED)
	{
		Menu menu;
		menu.render(renderer, font);

		waitingMenuSelection(menu);

		switch (menu.getCurrentSelection())  // NOLINT(clang-diagnostic-switch-enum)
		{
		case MENU_START_GAME:
		{
			auto score = gameLoop(gameState);
			if (gameState == GAME_STATE_ROUND_FINISHED)
			{
				saveScore(score);
			}
			break;
		}
		case MENU_HIGH_SCORES:
			break;
		default:
			gameState = GAME_STATE_EXITED;
			break;
		}

		SDL_Delay(50);
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

void waitingMenuSelection(Menu& menu)
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
			menu.setCurrentSelection(MENU_EXIT);
			return;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
			{
				return;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				menu.setCurrentSelection(MENU_EXIT);
				return;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				menu.select(-1);
				break;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				menu.select(1);
				break;
			}
			break;
		default:
			break;
		}

		menu.render(renderer, font);
	}
}

Uint32 gameLoop(GameState& gameState)
{
	Snake snake;
	Target target(&snake);
	Score score;

	gameState = GAME_STATE_RUNNING;
	Uint32 lastFrameTime = 0;

	setup(lastFrameTime);

	while (gameState == GAME_STATE_RUNNING)
	{
		processInput(snake, gameState);
		update(snake, target, score, lastFrameTime);
		if (check(snake) == true)
		{
			gameState = GAME_STATE_ROUND_FINISHED;
		}
		render(snake, target);
	}

	if (gameState == GAME_STATE_ROUND_FINISHED)
	{
		char str[50];
		snprintf(str, 50, "Your score: %d", score.getScore());  // NOLINT(cert-err33-c)
		showMessage(str, false, renderer, font);
		SDL_Delay(3000);
	}

	return score.getScore();
}

void setup(Uint32& lastFrameTime)
{
	lastFrameTime = SDL_GetTicks();
}

void processInput(Snake& snake, GameState& gameState)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		gameState = GAME_STATE_EXITED;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			gameState = GAME_STATE_EXITED;
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

bool check(Snake& snake)
{
	const Pos head = snake.getHeadPos();

	if (head.x >= WINDOW_WIDTH ||
		head.x <= 0 ||
		head.y >= WINDOW_HEIGHT ||
		head.y <= 0)
	{
		return true;
	}

	if (snake.checkHeadBodyCollision() == true)
	{
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

void saveScore(Uint32 score)
{
	NameBoard nameBoard;
	nameBoard.render(renderer, font);

	auto confirmed = isConfirmed(nameBoard);

	if (confirmed == false)
	{
		return;
	}
}

bool isConfirmed(NameBoard& nameBoard)
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
			if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
			{
				auto selection = nameBoard.getSelection();
				if (selection < ALPHABET_SIZE)
				{
					nameBoard.appendToName();
				}
				else if (selection == ALPHABET_SIZE)
				{
					nameBoard.backspaceName();
				}
				else if (selection == ALPHABET_SIZE + 1)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return false;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				nameBoard.changeCurrentPos(0, -1);
				break;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				nameBoard.changeCurrentPos(0, 1);
				break;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				nameBoard.changeCurrentPos(-1, 0);
				break;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				nameBoard.changeCurrentPos(1, 0);
				break;
			}
			break;
		default:
			break;
		}

		nameBoard.render(renderer, font);
	}
}

void close()
{
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
