#include <iostream>
#include <cmath>

using namespace std;

int stonetopound(int);

int main()
{
    int stone;
    cout << "Enter the weight in stone: ";
    cin >> stone;
    int pounds = stonetopound(stone);
    cout << stone << " stone = ";
    cout << pounds << " pounds." << endl;

    return 0;
}

int stonetopound(int stone)
{
    return 14 * stone;
}
