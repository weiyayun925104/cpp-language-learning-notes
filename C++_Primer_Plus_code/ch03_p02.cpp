#include <iostream>
#include <cmath>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    const int Foot_inch = 12;
    const double Inch_metr = 0.0254;
    const double kg_pound = 2.2;

    int height_foot = 0;
    std::cout << "How many foot are in you: ___\b\b\b";
    std::cin >> height_foot;

    int height_inch = 0;
    std::cout << "How many inches are in you: __\b\b";
    std::cin >> height_inch;

    int weight_and_pounds = 0;
    std::cout << "Enter your weight in pounds: ___\b\b\b";
    std::cin >> weight_and_pounds;

    height_inch += height_foot * Foot_inch;

    double height_meters = height_inch * Inch_metr;

    double weight_in_kilograms = weight_and_pounds / kg_pound;

    double bmi = weight_in_kilograms / pow(height_meters, 2);

    std::cout << "BMI = " << bmi << std::endl;

    return 0;
}
