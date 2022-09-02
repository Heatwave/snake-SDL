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

char* readFromFile(const char* filename)
{
	SDL_RWops* rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL) return NULL;

	Sint64 res_size = SDL_RWsize(rw);
	char* res = (char*)malloc(res_size + 1);

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}

	res[nb_read_total] = '\0';
	return res;
}

void write2File(const char* filename, const char* str)
{
	SDL_RWops* rw = SDL_RWFromFile(filename, "w");
	if (rw != NULL) {
		size_t len = SDL_strlen(str);
		if (SDL_RWwrite(rw, str, 1, len) != len) {
			SDL_Log("Couldn't fully write string\n");
		}
		else {
			SDL_Log("Wrote %d 1-byte blocks\n", len);
		}
		SDL_RWclose(rw);
	}
}
