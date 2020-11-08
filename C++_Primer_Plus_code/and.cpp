#include <iostream>

using namespace std;

const int ArSize = 6;

int main()
{
    double naaq[ArSize];
    cout << "Enter the NAAQs (New Age Awareness Quotients) of your neighbors.\n";
    cout << "Program terminates when you make " << ArSize << " entries "
         << "or enter a negative value.\n";

    int i = 0;
    double temp;
    cout << "First value: ";
    cin >> temp;
    while (i < ArSize && temp >= 0)
    {
        naaq[i] = temp;
        ++i;
        if (i < ArSize)
        {
            cout << "Next value: ";
            cin >> temp;
        }
    }
    if (i == 0)
    {
        cout << "No data, bye.\n";
    }
    else
    {
        cout << "Enter your NAAQ: ";
        double you;
        cin >> you;
        int count = 0;
        for (int j = 0; j < i; j++)
        {
            if (naaq[j] > you)
            {
                ++count;
            }
        }
        cout << count << " of your neighbors have greater awareness of the New Age than you do.\n";
    }

    return 0;
}
