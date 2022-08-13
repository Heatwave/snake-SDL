#include "Menu.h"

#include "constants.h"

void Menu::select(int change)
{
	if (change == 1 && this->currentSelection != MENU_EXIT)
	{
		this->currentSelection = static_cast<MENU_ITEM>(this->currentSelection + 1);
	}
	if (change == -1 && this->currentSelection != MENU_START_GAME)
	{
		this->currentSelection = static_cast<MENU_ITEM>(this->currentSelection - 1);
	}
}


void Menu::render(SDL_Renderer* renderer, TTF_Font* font) const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	constexpr SDL_Color unselectedColor = {0xFF, 0xFF, 0xFF, 0}; // white
	constexpr SDL_Color selectedColor = {0x4A, 0x86, 0xE8, 0}; // light blue

	SDL_Surface* text[MENU_LENGTH];
	SDL_Texture* texture[MENU_LENGTH];

	int rectY = WINDOW_HEIGHT / 10 * 3;

	for (int i = 0; i < MENU_LENGTH; ++i)
	{
		text[i] = TTF_RenderUTF8_Solid(font, this->menuTitles[i].c_str(),
		                               this->currentSelection == i ? selectedColor : unselectedColor);

		SDL_Rect messageRect;
		messageRect.x = (WINDOW_WIDTH - text[i]->w) / 2;
		rectY += i == 0 ? 0 : text[i - 1]->h + text[i]->h / 2;
		messageRect.y = rectY;
		messageRect.w = text[i]->w;
		messageRect.h = text[i]->h;

		texture[i] = SDL_CreateTextureFromSurface(renderer, text[i]);

		SDL_RenderCopy(renderer, texture[i], nullptr, &messageRect);
	}

	SDL_RenderPresent(renderer);

	for (int i = 0; i < MENU_LENGTH; ++i)
	{
		SDL_FreeSurface(text[i]);
		SDL_DestroyTexture(texture[i]);
	}
}

MENU_ITEM Menu::getCurrentSelection() const
{
	return currentSelection;
}

void Menu::setCurrentSelection(MENU_ITEM selection)
{
	this->currentSelection = selection;
}
