#include <iostream>
#include <string>

using namespace std;

int main()
{
    string stout = "Stout";
    string IPA = "IPA";
    string wheatBeer = "Wheat Beer";
    string ale = "Ale";
    string beerChoice = "";

    do
    {
        cout << "Please specify which type of beer you would like:" << "\n" <<
             "\t" << stout << "\n"
             "\t" << IPA << "\n"
             "\t" << wheatBeer << "\n"
             "\t" << ale << "\n";

        getline(cin, beerChoice, '\n');
    }
    while ( (beerChoice != stout) &&
            (beerChoice != IPA) &&
            (beerChoice != wheatBeer) &&
            (beerChoice != ale) );

    cout << "Good choice!" << endl;
}
