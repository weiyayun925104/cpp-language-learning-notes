#include <iostream>

using namespace std;

int main()
{
    cout << "Enter the starting countdown value: ";
    int limit = 0;
    cin >> limit;
    if (limit <= 0 )
    {
        return 0;
    }
    int i;
    for (i = limit; i; i--)
    {
        cout << "i = " << i << "\n";
    }
    cout << "Done, now i = " << i << "\n";

    return 0;
}
