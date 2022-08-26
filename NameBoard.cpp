#include "NameBoard.h"

NameBoard::NameBoard()
{
	for (size_t i = 0; i < 100; i++)
	{
		for (size_t j = 0; j < 100; j++)
		{
			this->possiablePos[i][j] = 0;
		}
	}
}

NameBoard::~NameBoard()
{
}

void NameBoard::changeCurrentPos(int x, int y)
{
	auto nextX = this->current.x + x;
	auto nextY = this->current.y + y;

	if (nextX < 0 || nextY < 0)
	{
		return;
	}

	if (this->possiablePos[nextX][nextY] == 1)
	{
		this->current.x += x;
		this->current.y += y;
		return;
	}

	if (this->possiablePos[0][nextY] == 1)
	{
		this->current.x = 0;
		this->current.y += y;
		return;
	}
}

void NameBoard::appendToName()
{
	if (this->name.size() >= 16)
	{
		return;
	}

	auto letter = this->alphabet[this->selection];
	this->name += letter;
}

void NameBoard::backspaceName()
{
	if (this->name.empty())
	{
		return;
	}
	this->name.pop_back();
}

void NameBoard::render(SDL_Renderer* renderer, TTF_Font* font)
{
	Pos option = { 0, 0 };

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
			option.x = 0;
			option.y += 1;
		}
		else if (i != 0)
		{
			rectX += 75;
			option.x += 1;
		}
		messageRect.x = rectX;
		messageRect.y = rectY;
		messageRect.w = TEXT_WIDTH;
		messageRect.h = TEXT_HEIGHT;

		texture[i] = SDL_CreateTextureFromSurface(renderer, text[i]);

		SDL_RenderCopy(renderer, texture[i], nullptr, &messageRect);

		this->possiablePos[option.x][option.y] = 1;

		if (this->current.x == option.x && this->current.y == option.y)
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_Rect outlinedQuad = { messageRect.x - 4, messageRect.y - 4, messageRect.w + 4, messageRect.h + 4 };
			SDL_RenderDrawRect(renderer, &outlinedQuad);
			this->selection = i;
		}
	}

	auto backspaceText = TTF_RenderUTF8_Solid(font, this->BACKSPACE.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10;
	rectY += WINDOW_HEIGHT / 10;
	msgRect.y = rectY;
	msgRect.w = backspaceText->w;
	msgRect.h = backspaceText->h;
	auto backspaceTexture = SDL_CreateTextureFromSurface(renderer, backspaceText);
	SDL_RenderCopy(renderer, backspaceTexture, nullptr, &msgRect);

	option.x = 0;
	option.y += 1;
	this->possiablePos[option.x][option.y] = 1;

	if (this->current.x == option.x && this->current.y == option.y)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_Rect outlinedQuad = { msgRect.x - 4, msgRect.y - 4, msgRect.w + 4, msgRect.h + 4 };
		SDL_RenderDrawRect(renderer, &outlinedQuad);
		this->selection = ALPHABET_SIZE;
	}

	auto confirmText = TTF_RenderUTF8_Solid(font, this->CONFIRM.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10 * 3;
	rectY += WINDOW_HEIGHT / 10 * 2;
	msgRect.y = rectY;
	msgRect.w = confirmText->w;
	msgRect.h = confirmText->h;
	auto confirmTexture = SDL_CreateTextureFromSurface(renderer, confirmText);
	SDL_RenderCopy(renderer, confirmTexture, nullptr, &msgRect);

	option.x = 0;
	option.y += 1;
	this->possiablePos[option.x][option.y] = 1;

	if (this->current.x == option.x && this->current.y == option.y)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_Rect outlinedQuad = { msgRect.x - 4, msgRect.y - 4, msgRect.w + 4, msgRect.h + 4 };
		SDL_RenderDrawRect(renderer, &outlinedQuad);
		this->selection = ALPHABET_SIZE + 1;
	}

	auto cancelText = TTF_RenderUTF8_Solid(font, this->CANCEL.c_str(), white);
	msgRect.x = WINDOW_WIDTH / 10 * 6;
	msgRect.y = rectY;
	msgRect.w = cancelText->w;
	msgRect.h = cancelText->h;
	auto cancelTexture = SDL_CreateTextureFromSurface(renderer, cancelText);
	SDL_RenderCopy(renderer, cancelTexture, nullptr, &msgRect);

	option.x += 1;
	this->possiablePos[option.x][option.y] = 1;

	if (this->current.x == option.x && this->current.y == option.y)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_Rect outlinedQuad = { msgRect.x - 4, msgRect.y - 4, msgRect.w + 4, msgRect.h + 4 };
		SDL_RenderDrawRect(renderer, &outlinedQuad);
		this->selection = ALPHABET_SIZE + 2;
	}

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

bool NameBoard::isNameEmpty() const
{
	return this->name.empty();
}

std::string NameBoard::getName() const
{
	return this->name;
}

size_t NameBoard::getSelection() const
{
	return this->selection;
}
