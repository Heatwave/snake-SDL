#pragma once
#ifndef CONSTANS_H
#define CONSTANS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FONT_FILE_NAME "arial.ttf"
#define FONT_SIZE_PT 30

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

typedef struct Pos
{
	int x, y;
} Pos;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#endif // !CONSTANS_H
