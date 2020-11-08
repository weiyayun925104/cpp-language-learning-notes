#include <iostream>
#include <cstring>
#include "list.h"


void some_func1(std::string &str);
void some_func2(std::string &str);

int main()
{
    List Game;

    std::string games[MAX] =
    {
        "Dota 2",
        "CS:GO",
        "PRAY",
        "ArcheAge",
        "Loong online"
    };


    for (int i = 0; i < MAX; i++)
    {
        Game.add_element(games[i]);
    }


    Game.show_list();
    std::cout << '\n';
    Game.visit_element(some_func1);
    Game.show_list();
    std::cout << '\n';

    Game.visit_element(some_func2);
    Game.show_list();

    return 0;
}

void some_func1(std::string &str)
{
    int size = str.size();
    for (int i = 0; i < size; ++i)
    {
        str[i] = toupper(str[i]);
    }
}

void some_func2(std::string &str)
{
    int size = str.size();
    for (int i = 0; i < size; ++i)
    {
        str[i] = tolower(str[i]);
    }
}
