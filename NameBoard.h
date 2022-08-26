#pragma once
#ifndef SNAKE_NAME_BOARD_H
#define SNAKE_NAME_BOARD_H

#include <string>
#include <vector>
#include <set>
#include <SDL.h>
#include <SDL_ttf.h>

#include "constants.h"

constexpr auto ALPHABET_SIZE = 26;

class NameBoard
{
public:
	NameBoard();

	~NameBoard();

	void changeCurrentPos(int x, int y);

	void appendToName();

	void backspaceName();

	void render(SDL_Renderer*, TTF_Font*);

	bool isNameEmpty() const;

	std::string getName() const;

	size_t getSelection() const;

private:
	Pos current = { 0,0 };

	int possiablePos[100][100];

	size_t selection = 0;

	std::string name = "";

	const std::string YOUR_NAME = "Your name:  ";
	const std::string BACKSPACE = "Backspace";
	const std::string CONFIRM = "Confirm";
	const std::string CANCEL = "Cancel";

	const std::string alphabet[ALPHABET_SIZE] = { "A", "B", "C", "D", "E", "F", "G",
		"H", "I", "J", "K", "L", "M", "N",
		"O", "P", "Q", "R", "S", "T",
		"U", "V", "W", "X", "Y", "Z" };
};

#endif // !SNAKE_NAME_BOARD_H
