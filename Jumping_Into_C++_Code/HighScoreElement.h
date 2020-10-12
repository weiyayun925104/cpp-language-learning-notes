#pragma once
#ifndef HIGHSCOREELEMENT_H_
#define HIGHSCOREELEMENT_H_

#include <string>

using namespace std;

class HighScoreElement
{
public:
	HighScoreElement(string name, int score);

	string getName() const;
	int getScore() const;

	int compare(HighScoreElement& other);
private:
	string _name;
	int _score;
};

#endif
