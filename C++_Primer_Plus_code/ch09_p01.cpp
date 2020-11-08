#include <iostream>
#include "golf.h"

int main()
{
    golf ann;
    setgolf(ann, "Ann Birdfree", 24);
    showgolf(ann);

    int col_players = 0;
    std::cout << "Enter the number of players: ";
    (std::cin >> col_players).get();

    golf *players = new golf[col_players];
    int i;
    for (i = 0; i < col_players; i++)
    {
        if (setgolf(players[i]) == 0)
        {
            break;
        }
    }

    for (int j = 0; j < i; j++)
    {
        showgolf(players[j]);
    }

    delete [] players;

    return 0;
}
