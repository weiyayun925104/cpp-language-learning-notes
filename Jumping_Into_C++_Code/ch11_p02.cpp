#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct EnemySpaceShip
{
    int xCoordinate;
    int yCoordinate;
    int weaponPower;
};

int const screenWidth = 1024;
int const screenHeight = 768;
int const maxNumberOfShips = 50;
int const moveScale = 10;

int randRange(int low, int high);
bool shipIsOnScreen(EnemySpaceShip ship);
bool shipsOnScreen(EnemySpaceShip ships[], int numberOfShips);
void printFleet(EnemySpaceShip fleet[], int numberOfShips);


int main()
{
    srand( time(nullptr) );

    cout << "Enter the number of 50 or fewer space ships that you want to fly around:\n";

    int numberOfShips;
    cin >> numberOfShips;
    if (numberOfShips > maxNumberOfShips)
    {
        numberOfShips = maxNumberOfShips;
    }

    int weaponHigh = 10;
    int weaponLow = 1;

    EnemySpaceShip fleet[maxNumberOfShips];
    for (int i = 0; i < numberOfShips; i++)
    {
        fleet[i].weaponPower = randRange(weaponLow, weaponHigh);
        fleet[i].xCoordinate = randRange(0, screenWidth);
        fleet[i].yCoordinate = randRange(0, screenHeight);
    }
    printFleet(fleet, numberOfShips);

    do
    {
        cout << "==================== Moving Ships that are Still On Screen ================================\n";
        for (int i = 0; i < numberOfShips; i++)
        {
            if ( shipIsOnScreen(fleet[i]) )
            {
                fleet[i].xCoordinate += randRange(-3 * moveScale, 3 * moveScale);
                fleet[i].yCoordinate += randRange(-3 * moveScale, 3 * moveScale);
            }
        }
        printFleet(fleet, numberOfShips);

    }
    while ( shipsOnScreen(fleet, numberOfShips) );

    cout << "All ships have left the " << screenWidth << "px X " << screenHeight << "px screen.";
}

void printFleet(EnemySpaceShip fleet[], int numberOfShips)
{
    for (int i = 0; i < numberOfShips; i++)
    {
        cout << "Ship # " << i + 1 << " (" << fleet[i].xCoordinate << ',' << fleet[i].yCoordinate << ')' << " Weapon power: " << fleet[i].weaponPower << '\n';
    }
}

int randRange(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

bool shipsOnScreen(EnemySpaceShip ships[], int numberOfShips)
{
    for (int i = 0; i < numberOfShips; i++)
    {
        if (shipIsOnScreen(ships[i]))
        {
            return true;
        }
    }
    return false;
}

bool shipIsOnScreen(EnemySpaceShip ship)
{
    return ( (0 <= ship.xCoordinate && ship.xCoordinate <= screenWidth) &&
            (0 <= ship.yCoordinate && ship.yCoordinate <= screenHeight) );
}
