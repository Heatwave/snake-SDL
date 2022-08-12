#include "utils.h"

bool checkPosOverlap(Pos src, Pos dst)
{
	if (src.x == dst.x && src.y == dst.y)
	{
		return true;
	}
	return false;
}

int floorInt(int num, int base)
{
	const int modNum = num % base;
	if (modNum == 0)
	{
		return num;
	}
	return num - modNum;
}

void showMessage(const char* message, bool clear, SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Rect messageRect;

	constexpr SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };

	SDL_Surface* text = TTF_RenderUTF8_Solid(font, message, white);

	messageRect.x = (WINDOW_WIDTH - text->w) / 2;
	messageRect.y = (WINDOW_HEIGHT - text->h) / 2;
	messageRect.w = text->w;
	messageRect.h = text->h;
	SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, text);

	if (clear == true)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);
	}

	SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(text);
	SDL_DestroyTexture(messageTexture);
}
