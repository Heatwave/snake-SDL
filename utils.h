#pragma once
#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "constants.h"

struct classcomp {
	bool operator() (const std::pair<std::string, size_t>& lhs, const std::pair<std::string, size_t>& rhs) const
	{
		if (lhs.second == rhs.second)
		{
			return lhs.first < rhs.first;
		}
		return lhs.second > rhs.second;
	}
};

bool checkPosOverlap(Pos, Pos);
int floorInt(int, int);
void showMessage(const char*, bool, SDL_Renderer*, TTF_Font*);
char* readFromFile(const char*);
void write2File(const char*, const char*);

#endif // !SNAKE_UTILS_H
