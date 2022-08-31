#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::readFileToScores(const char* content)
{
	auto fileSize = strlen(content);
	SDL_Log("file size: %u", fileSize);
	//SDL_Log(content);

	if (fileSize == 0)
	{
		return;
	}

	size_t pos = 0;
	char nameStore[256];
	nameStore[0] = '\0';
	char numberStore[256];
	numberStore[0] = '\0';
	size_t tempCur = 0;
	while (pos <= fileSize)
	{
		auto c = *(content + pos);
		if (c >= 'A' && c <= 'Z')
		{
			if (tempCur < sizeof(nameStore))
			{
				nameStore[tempCur++] = c;
			}
			nameStore[tempCur] = '\0';
		}
		else if (c >= '0' && c <= '9')
		{
			if (tempCur < sizeof(numberStore))
			{
				numberStore[tempCur++] = c;
			}
			numberStore[tempCur] = '\0';
		}
		else
		{

			if (strlen(numberStore) > 0 && strlen(nameStore) > 0)
			{
				this->scores.insert(std::pair<std::string, size_t>(std::string(nameStore), atoi(numberStore)));
				nameStore[0] = '\0';
				numberStore[0] = '\0';
			}
			tempCur = 0;
		}
		pos++;
	}

	//this->scores.insert(std::pair<std::string, size_t>("STAN", 20));
	//this->scores.insert(std::pair<std::string, size_t>("STAN", 10));

	for (auto it = this->scores.begin(); it != this->scores.end(); it++)
	{
		SDL_Log("%s %u", it->first.c_str(), it->second);
	}
}

void ScoreBoard::render(SDL_Renderer* renderer, TTF_Font* font) const
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

	auto it = this->scores.begin();

	for (Uint8 i = 0; i < 5; i++)
	{
		std::string msg = std::to_string(i + 1) + ". ";
		if (it != this->scores.end())
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
