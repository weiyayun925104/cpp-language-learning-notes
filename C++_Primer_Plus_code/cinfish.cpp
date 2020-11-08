#include <iostream>

using namespace std;

const int Max = 5;

int main()
{
    double fish[Max];
    cout << "Please enter the weights of your fish.\n";
    cout << "You may enter up to " << Max << " fish or enter q to terminate.\n";
    cout << "fish #1: ";
    int i = 0;
    while (i < Max && cin >> fish[i])
    {
        if (++i < Max)
        {
            cout << "fish #" << i + 1 << ": ";
        }
    }
    cin.clear();
    double total = 0.0;
    for (int j = 0; j < i; j++)
    {
        total += fish[j];
    }

    if (i == 0)
    {
        cout << "No fish, bye.\n";
    }
    else
    {
        cout << "average weight of " << i << " fish = "  << total / i << endl;
    }
    cout << "Done.\n";

    return 0;
}
