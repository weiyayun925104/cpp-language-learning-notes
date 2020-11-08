#include <iostream>

using namespace std;

int main()
{
    int chest = 42;
    int waist = 42;
    int inseam = 42;

    cout << "Monsieur cuts a striking figure!\n";
    cout << "Chest = " << chest << " (decimal for 42)\n";
    cout << hex << "Waist = " << waist << " (hexadecimal for 42)\n";
    cout << oct << "inseam = " << inseam << " (octal for 42)\n";

    return 0;
}
