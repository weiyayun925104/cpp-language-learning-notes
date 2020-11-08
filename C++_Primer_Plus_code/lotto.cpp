#include <iostream>

using namespace std;

long double probability(int numbers, int picks);

int main()
{
    double total, choices;
    cout << "Enter the total number of choices on the game card and\n";
    cout << "the number of picks allowed:\n";
    while ( (cin >> total) && (cin >> choices) && choices <= total )
    {
        cout << "You have one chance in " << probability(total, choices) << " of winning. \n";
        cout << "Next two numbers (q to quit) : ";
    }
    cout << "Done.\n";

    return 0;
}
long double probability(int numbers, int picks)
{
    long double result = 1.0;
    long double n;
    int p;
    for (n = numbers, p = picks; p > 0; n--, p--)
    {
        result = result * n / p;
    }
    return result;
}
