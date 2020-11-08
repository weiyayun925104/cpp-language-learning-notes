#include <iostream>
#include <cmath>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    const double mile_km = 1.609;
    const double gl_litr = 3.785;

    std::cout << "Enter the number of liters per 100 kilometers: ";
    double litr_100km = 0.0;
    std::cin >> litr_100km;

    double mile_gl = 100 / ( litr_100km * (mile_km / gl_litr) );

    std::cout << "Answer " << mile_gl << " Miles per gallon" << std::endl;

    return 0;
}
