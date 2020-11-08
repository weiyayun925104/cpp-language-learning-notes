#include <iostream>
#include "wine.h"

int main()
{
    std::cout << "Enter name of wine: ";
    char lab[50];
    std::cin.getline(lab, 50);
    std::cout << std::endl;

    std::cout << "Enter number of years: ";
    int yrs = 0;
    std::cin >> yrs;
    while (std::cin.get() != '\n')
    {
        continue;
    }

    Wine holding(lab, yrs);
    holding.GetBottles();
    holding.Show();
    std::cout << std::endl;

    const int YRS = 3;
    int y[YRS] = { 1993, 1995, 1998 };
    int b[YRS] = { 48, 60, 72 };

    Wine more("Gushing Grape Red", YRS, y, b);
    more.Show();
    std::cout << std::endl;

    std::cout << "Total bottles for " << more.Label();
    std::cout << ": " << more.sum() << std::endl;
    std::cout << "Done.\n";

    return 0;
}
