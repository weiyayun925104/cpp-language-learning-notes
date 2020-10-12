#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int randRange(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

int main()
{
    int sRandSeed = time(nullptr);
    srand(sRandSeed);

    cout << "Welcome to the slot machine game. \n";

    int minRange = 0;
    cout << "Please enter the minimum number to include: \n";
    cin >> minRange;

    int maxRange = 0;
    cout << "Please enter the maximum number to include: \n";
    cin >> maxRange;

    int randomNumber1 = randRange(minRange, maxRange);
    int randomNumber2 = randRange(minRange, maxRange);
    int randomNumber3 = randRange(minRange, maxRange);
    int guessedNumber1 = 0;
    int guessedNumber2 = 0;
    int guessedNumber3 = 0;
    bool stillGuessing = true;

    int option = 1;
    do
    {
        cout << "Enter any number to try again, or '0' to exit: " << '\n';
        cin >> option;
        if (option == 0)
        {
            cout << "You have chosen to forfeit your winnings!\n";
            return 1;
        }
        guessedNumber1 = randRange(minRange, maxRange);
        guessedNumber2 = randRange(minRange, maxRange);
        guessedNumber3 = randRange(minRange, maxRange);

        cout << "Results are: " << guessedNumber1 << " - " << guessedNumber2 << " - " << guessedNumber3 << '\n';

        if ((guessedNumber1 == randomNumber1) &&
                (guessedNumber2 == randomNumber2) &&
                (guessedNumber3 == randomNumber3))
        {
            stillGuessing = false;
        }
    }
    while (stillGuessing);

    cout << "Congratulations! You are a WINNER! \n";
}
