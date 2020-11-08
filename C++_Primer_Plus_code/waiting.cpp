#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    cout << "Enter the delay time, in seconds: ";
    double sees;
    cin >> sees;
    clock_t delay = sees * CLOCKS_PER_SEC;
    cout << "starting\n";
    clock_t start = clock();
    while (clock() - start < delay)
        ;
    cout << "done\n";

    return 0;
}
