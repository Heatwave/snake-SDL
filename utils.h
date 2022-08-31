#pragma once
#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"

bool checkPosOverlap(Pos, Pos);
int floorInt(int, int);
void showMessage(const char*, bool, SDL_Renderer*, TTF_Font*);
char* readFromFile(const char*);

#endif // !SNAKE_UTILS_H
