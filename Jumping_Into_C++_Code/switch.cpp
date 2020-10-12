#include <iostream>

using namespace std;

void playgame ()
{
    cout << "This is playgame.\n";
}
void loadgame ()
{
    cout << "This is loadgame.\n";
}
void playmultiplayer ()
{
    cout << "This is playmultiplayer.\n";
}

int main ()
{
    int input;
    cout << "1. Play game\n";
    cout << "2. Load game\n";
    cout << "3. Play multiplayer\n";
    cout << "4. Exit\n";
    cout << "Selection: ";
    cin >> input;
    switch ( input )
    {
    case 1:
        playgame();
        break;
    case 2:
        loadgame();
        break;
    case 3:
        playmultiplayer();
        break;
    case 4:
        cout << "Thank you for playing!\n";
        break;
    default:
        cout << "Error, bad input, quitting\n";
        break;
    }
}
