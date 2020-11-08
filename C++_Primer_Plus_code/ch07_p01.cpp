#include <iostream>

double average_harmonic(double x, double y);

int main()
{
    double x = 0;
    double y = 0;
    std::cout << "Enter x and y: " << std::endl;

    while ( (std::cin >> x) && x != 0 && (std::cin >> y) && y != 0)
    {
        std::cout << "The average harmonic " << x << " and " << y << " = " << average_harmonic(x, y) << std::endl;
        std::cout << "Enter x and y: " << std::endl;
    }

    return 0;
}
double average_harmonic(double x, double y)
{
    return  (2.0 * x * y) / (x + y);
}
