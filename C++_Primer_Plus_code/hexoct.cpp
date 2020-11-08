#include <iostream>

using namespace std;

int main()
{
    int chest = 42;
    int waist = 0x42;
    int inseam = 042;

    cout << "Monsieur cuts a striking figure!\n";
    cout << "Chest = " << chest << " (42 in decimal)\n";
    cout << "Waist = " << waist << " (0x42 in hex)\n";
    cout << "inseam = " << inseam << " (042 in octal)\n";

    return 0;
}
