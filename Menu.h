#pragma once
#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

enum MENU_ITEM
{
	MENU_START_GAME,
	MENU_HIGH_SCORES,
	MENU_EXIT,
	MENU_LENGTH
};

class Menu
{
public:
	Menu() = default;

	void select(int);

	void render(SDL_Renderer*, TTF_Font*) const;

	MENU_ITEM getCurrentSelection() const;

	void setCurrentSelection(MENU_ITEM);

private:
	MENU_ITEM currentSelection = MENU_START_GAME;
	std::string menuTitles[MENU_LENGTH] = {"Start Game", "High Scores", "Exit"};
};

#endif
