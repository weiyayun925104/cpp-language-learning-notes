#include <iostream>
#include "golf_class.h"

int main()
{
    Golf ann;
    ann = Golf("Ann Birdfree", 24);
    ann.show_golf();

    std::cout << "Enter the number of players: ";
    int col_players = 0;
    (std::cin >> col_players).get();
    std::cout << std::endl;

    Golf *players = new Golf[col_players];
    int i;
    for (i = 0; i < col_players; i++)
    {
        if (players[i].set_golf() == 0)
        {
            break;
        }
    }

    for (int j = 0; j < i; j++)
    {
        players[j].show_golf();
    }

    delete [] players;

    return 0;
}
