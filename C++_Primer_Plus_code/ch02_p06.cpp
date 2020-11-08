
#include <iostream>

double light_years(double light_years);

int main()
{
    std::cout << "Enter the number of light years: ";

    double lightyears = 0;
    std::cin >> lightyears;

    std::cout << lightyears << " light year = " << light_years(lightyears) << " astronomical units\n";

    return 0;
}

double light_years(double light_years)
{
    return light_years * 63240;
}
