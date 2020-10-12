#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int randRange(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

int main()
{
    int sRandSeed = time(nullptr);
    srand(sRandSeed);

    int keepFlippingCoins = 1;
    do
    {
        cout << "Enter the number of coin flips to do. Enter 0 to stop.\n";
        cin >> keepFlippingCoins;
        for (size_t i = 0; i < keepFlippingCoins; i++)
        {
            int coinNumber = randRange(1, 2);
            string face = "";
            if (coinNumber == 1)
            {
                face = "Heads\n";
            }
            else
            {
                face = "Tails\n";
            }
            cout << face;
        }
    }
    while (keepFlippingCoins != 0);
}
