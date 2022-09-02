#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::render(SDL_Renderer* renderer, TTF_Font* font, std::set<std::pair<std::string, size_t>, classcomp>& scores) const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	constexpr SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };

	std::string msg = "High Scores";
	auto text = TTF_RenderUTF8_Solid(font, msg.c_str(), white);
	SDL_Rect msgRect{};
	msgRect.x = WINDOW_WIDTH / 2 - text->w / 2;
	msgRect.y = WINDOW_HEIGHT / 10;
	msgRect.w = text->w;
	msgRect.h = text->h;
	auto texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, texture, nullptr, &msgRect);

	SDL_FreeSurface(text);
	SDL_DestroyTexture(texture);

	auto it = scores.begin();

	for (Uint8 i = 0; i < 5; i++)
	{
		std::string msg = std::to_string(i + 1) + ". ";
		if (it != scores.end())
		{
			msg += it->first;
			msg += " ";
			msg += std::to_string(it->second);
			it++;
		}
		text = TTF_RenderUTF8_Solid(font, msg.c_str(), white);
		SDL_Rect msgRect{};
		msgRect.x = WINDOW_WIDTH / 10;
		msgRect.y = WINDOW_HEIGHT / 10 * (i + 2);
		msgRect.w = text->w;
		msgRect.h = text->h;
		texture = SDL_CreateTextureFromSurface(renderer, text);
		SDL_RenderCopy(renderer, texture, nullptr, &msgRect);

		SDL_FreeSurface(text);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(renderer);
}
