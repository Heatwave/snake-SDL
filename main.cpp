#include<SDL.h>
#include<stdio.h>

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL init failed! Error: %s\n", SDL_GetError());
		return -1;
	}

	printf("SDL init successed!");

	SDL_Quit();

	return 0;
}
