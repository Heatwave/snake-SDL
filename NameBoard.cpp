#include "NameBoard.h"
#include "constants.h"

NameBoard::NameBoard()
{
}

NameBoard::~NameBoard()
{
}

void NameBoard::render(SDL_Renderer* renderer, TTF_Font* font) const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	constexpr SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };

	std::string msg = this->YOUR_NAME + this->name;
	auto nameText = TTF_RenderUTF8_Solid(font, msg.c_str(), white);
	SDL_Rect msgRect{};
	msgRect.x = WINDOW_WIDTH / 2 - nameText->w / 2;
	msgRect.y = WINDOW_HEIGHT / 10;
	msgRect.w = nameText->w;
	msgRect.h = nameText->h;
	auto nameTexture = SDL_CreateTextureFromSurface(renderer, nameText);
	SDL_RenderCopy(renderer, nameTexture, nullptr, &msgRect);

	SDL_Surface* text[ALPHABET_SIZE]{};
	SDL_Texture* texture[ALPHABET_SIZE]{};

	auto TEXT_WIDTH = 30;
	auto TEXT_HEIGHT = 40;

	auto rectX = WINDOW_WIDTH / 10;
	auto rectY = WINDOW_HEIGHT / 10 * 3;

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		text[i] = TTF_RenderUTF8_Solid(font, this->alphabet[i].c_str(), white);

		SDL_Rect messageRect{};
		if (rectX + TEXT_WIDTH + 100 >= WINDOW_WIDTH)
		{
			rectX = WINDOW_WIDTH / 10;
			rectY += TEXT_HEIGHT + WINDOW_HEIGHT / 10 / 2;
		}
		else if (i != 0)
		{
			rectX += 75;
		}
		messageRect.x = rectX;
		messageRect.y = rectY;
		messageRect.w = TEXT_WIDTH;
		messageRect.h = TEXT_HEIGHT;

		texture[i] = SDL_CreateTextureFromSurface(renderer, text[i]);

		SDL_RenderCopy(renderer, texture[i], nullptr, &messageRect);
	}

	auto backspaceText = TTF_RenderUTF8_Solid(font, this->BACKSPACE.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10;
	rectY += WINDOW_HEIGHT / 10;
	msgRect.y = rectY;
	msgRect.w = backspaceText->w;
	msgRect.h = backspaceText->h;
	auto backspaceTexture = SDL_CreateTextureFromSurface(renderer, backspaceText);
	SDL_RenderCopy(renderer, backspaceTexture, nullptr, &msgRect);

	auto confirmText = TTF_RenderUTF8_Solid(font, this->CONFIRM.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10 * 3;
	rectY += WINDOW_HEIGHT / 10 * 2;
	msgRect.y = rectY;
	msgRect.w = confirmText->w;
	msgRect.h = confirmText->h;
	auto confirmTexture = SDL_CreateTextureFromSurface(renderer, confirmText);
	SDL_RenderCopy(renderer, confirmTexture, nullptr, &msgRect);

	auto cancelText = TTF_RenderUTF8_Solid(font, this->CANCEL.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10 * 6;
	msgRect.y = rectY;
	msgRect.w = cancelText->w;
	msgRect.h = cancelText->h;
	auto cancelTexture = SDL_CreateTextureFromSurface(renderer, cancelText);
	SDL_RenderCopy(renderer, cancelTexture, nullptr, &msgRect);

	SDL_RenderPresent(renderer);

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		SDL_FreeSurface(text[i]);
		SDL_DestroyTexture(texture[i]);
	}

	SDL_FreeSurface(nameText);
	SDL_DestroyTexture(nameTexture);

	SDL_FreeSurface(backspaceText);
	SDL_DestroyTexture(backspaceTexture);

	SDL_FreeSurface(confirmText);
	SDL_DestroyTexture(confirmTexture);

	SDL_FreeSurface(cancelText);
	SDL_DestroyTexture(cancelTexture);
}
