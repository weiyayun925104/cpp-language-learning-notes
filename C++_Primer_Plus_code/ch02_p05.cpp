#include <iostream>

double celsius_to_fahrenheit(double celsius);

int main()
{
    std::cout << "Pleas enter a celsius value: ";

    double celsius = 0;
    std::cin >> celsius;

    std::cout << celsius << " degrees Celsius is " << celsius_to_fahrenheit(celsius) << " degrees fahrenheit\n";

    return 0;
}

double celsius_to_fahrenheit(double celsius)
{
    return (1.8 * celsius + 32.0);
}
