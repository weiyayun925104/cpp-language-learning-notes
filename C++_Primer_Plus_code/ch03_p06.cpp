#include <iostream>
#include <cmath>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    const int km_100 = 100;

    double kilometers = 0;
    std::cout << "Enter the distance in kilometers: ";
    std::cin >> kilometers;

    double litres = 0;
    std::cout << "Enter the amount of spent gasoline in litres: ";
    std::cin >> litres;

    double Result = ( (litres / kilometers) * km_100 );
    std::cout << "Fuel consumption: " << Result << "litres / 100km" << std::endl;

    return 0;
}
