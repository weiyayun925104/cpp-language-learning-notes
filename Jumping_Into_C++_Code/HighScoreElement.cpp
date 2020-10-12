#include <iostream>
#include <string>
#include "HighScoreElement.h"

using namespace std;

HighScoreElement::HighScoreElement(std::string name, int score)
{
    _name = name;
    _score = score;
}

int HighScoreElement::compare(HighScoreElement &other)
{
    if (this->_score < other._score)
    {
        return -1;
    }
    else if(this->_score > other._score)
    {
        return 1;
    }
    else if (this->_name < other._name)
    {
        return -1;
    }
    else if(this->_name > other._name)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


string HighScoreElement::getName() const
{
    return _name;
}

int HighScoreElement::getScore() const
{
    return _score;
}
