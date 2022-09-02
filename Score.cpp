#include "Score.h"

Score::Score()
{
	this->score = 0;
}

void Score::readFileToScores(const char* content)
{
	auto fileSize = strlen(content);

	if (fileSize == 0)
	{
		return;
	}

	size_t pos = 0;
	char nameStore[256]{};
	nameStore[0] = '\0';
	char numberStore[256]{};
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
}

void Score::setScore(Uint32 score)
{
	this->score = score;
}

Uint32 Score::getScore() const
{
	return this->score;
}

void Score::addNewName(std::string name)
{
	this->scores.insert(std::pair<std::string, size_t>(std::string(name), this->getScore()));

	while (this->scores.size() > 5)
	{
		this->scores.erase(--this->scores.cend());
	}
}

void Score::clearScores()
{
	this->scores.clear();
}

std::set<std::pair<std::string, size_t>, classcomp> Score::getScores() const
{
	return this->scores;
}

std::string Score::getScoresContent() const
{
	std::string content = "";

	for (auto it = this->scores.cbegin(); it != this->scores.cend(); ++it)
	{
		content += it->first + " ";
		content += std::to_string(it->second) + '\n';
	}

	return content;
}
