#include <iostream>
#include "tabletenn0.h"

TableTennisPlayer::TableTennisPlayer(const string & fn, const string & In, bool ht) : firstname(fn), lastname(In), hasTable(ht) 
{

}
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}
