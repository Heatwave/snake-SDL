#pragma once
#ifndef SNAKE_NAME_BOARD_H
#define SNAKE_NAME_BOARD_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

constexpr auto ALPHABET_SIZE = 26;

class NameBoard
{
public:
	NameBoard();

	~NameBoard();

	void render(SDL_Renderer*, TTF_Font*) const;

private:
	size_t current = 0;
	std::string name = "Stan";
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
