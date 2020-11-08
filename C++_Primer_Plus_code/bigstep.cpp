#include <iostream>

using namespace std;

int main()
{

    cout << "Enter an integer: ";
    int step;
    cin >> step;
    if (step <= 0)
    {
        return 0;
    }
    cout << "Counting by " << step << "\n";
    for (int i = 0; i < 100; i = i + step)
    {
        cout << i << endl;
    }

    return 0;
}
