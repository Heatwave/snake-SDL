#pragma once
#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

#include <SDL.h>
#include <string>
#include <set>

#include "utils.h"

class Score
{
public:
	Score();

	void readFileToScores(const char*);

	void setScore(Uint32);

	Uint32 getScore() const;

	void addNewName(std::string);

	void clearScores();

	std::set<std::pair<std::string, size_t>, classcomp> getScores() const;

	std::string getScoresContent() const;
private:
	Uint32 score;
	std::set<std::pair<std::string, size_t>, classcomp> scores;
};

#endif // !SNAKE_SCORE_H
