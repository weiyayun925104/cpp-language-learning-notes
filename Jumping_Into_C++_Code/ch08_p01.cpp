
#include <iostream>
#include <string>

using namespace std;

void SingNinetyNineBottlesSong()
{
    for (size_t beer = 99; beer > 0; beer--)
    {
        if (beer != 99)
        {
            cout << beer << " bottles of beer on the wall.\n";
        }
        cout << beer << " bottles of beer on the wall, " << beer << " bottles of beer.\n" <<
             "Take one down, pass it around...\n";
    }
}

int logIn()
{
    string password = "guest";
    string userInput = "";
    int attemptLimit = 5;

    for (size_t attempts = 0; attempts < attemptLimit; attempts++)
    {
        if (attempts > 0)
        {
            cout << "You entered an incorrect password! \n" <<
                 "Attempts remaining: " << attemptLimit - attempts << "\n";
        }
        cout << "Please enter your password" << "\n";
        cin >> userInput;
        if (userInput == password)
        {
            cout << "Congratulations! You have been granted access..." << "\n";
            return 0;
        }
    }
    cout << "Sadly we can't let you in. Goodbye :-( " << "\n";
    return 1;
}

int selectBeerChoice(string beerOptions[])
{
    int beerChoice = 0;

    cout << "Please specify which type of beer you would like:\n";
    cout << "\n\t " << "1 - " << beerOptions[0];
    cout << "\n\t " << "2 - " << beerOptions[1];
    cout << "\n\t " << "3 - " << beerOptions[2];
    cout << "\n\t " << "4 - " << beerOptions[3];

    cin >> beerChoice;
    return beerChoice;
}

bool validBeerChoice(int beerChoice)
{
    bool isValid = false;
    switch (beerChoice)
    {
    case 1:
        isValid = true;
        break;
    case 2:
        isValid = true;
        break;
    case 3:
        isValid = true;
        break;
    case 4:
        isValid = true;
        break;
    default:
        break;
    }
    return isValid;
}

int main()
{
    if (logIn() == 1)
    {
        return 1;
    }

    cin.clear();
    cin.ignore(80, '\n');

    string beerOptions[4] = { "Stout", "IPA", "Wheat Beer", "Ale" };
    int beerChoice = 0;

    do
    {
        beerChoice = selectBeerChoice(beerOptions);
    }
    while (!validBeerChoice(beerChoice));

    cout << "Good choice!" << endl;

    SingNinetyNineBottlesSong();
}
