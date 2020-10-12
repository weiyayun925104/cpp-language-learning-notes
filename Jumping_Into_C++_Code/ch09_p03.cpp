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

    int low = 1;
    int high = 100;
    int randomNumber = randRange(low, high);
    bool stillGuessing = true;

    cout << "Guess what random number I have chosen between " << low << " and " << high << '\n';

    int numberOfGuesses = 0;
    int lastGuessHigh = high;
    int lastGuessLow = low;
    do
    {
        int guessedNumber = lastGuessLow + (lastGuessHigh - lastGuessLow) / 2;
        if (guessedNumber < lastGuessLow)
        {
            guessedNumber = lastGuessLow;
        }
        if (guessedNumber > lastGuessHigh)
        {
            guessedNumber = lastGuessHigh;
        }
        cout << "Program is guessing " << guessedNumber << '\n';

        if (guessedNumber > randomNumber)
        {
            cout << "Your guess is too high!\n";
            if (lastGuessHigh == guessedNumber)
            {
                lastGuessHigh--;
            }
            else
            {
                lastGuessHigh = guessedNumber;
            }
        }
        else if (guessedNumber < randomNumber)
        {
            cout << "Your guess is too low!\n";
            if (lastGuessLow == guessedNumber)
            {
                lastGuessLow++;
            }
            else
            {
                lastGuessLow = guessedNumber;
            }
        }
        else
        {
            cout << "Correct!\n";
            stillGuessing = false;
        }
        numberOfGuesses++;
    }
    while (stillGuessing);

    cout << "The random number was guessed by the program in " << numberOfGuesses << " tries." << endl;
}
