#include <iostream>

using namespace std;

struct inflatable
{
    char name[32];
    double volume;
    double price;
};

int main()
{
    inflatable guest =
    {
        "Glorious Gloria",
        1.88,
        29.99
    };

    inflatable pal =
    {
        "Audacious Arthur",
        3.12,
        32.99
    };

    cout << "Expand your guest list with " << guest.name << " and " << pal.name << "!\n";
    cout << "You can have both for $" << guest.price + pal.price << "!\n";

    return 0;
}
