#include <iostream>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    const int Foot_inch = 12;
    const double Inch_sm = 2.54;

    double Growth = 0;
    std::cout << "Enter your height in centimeters: ___\b\b\b";
    std::cin >> Growth;

    double Growth_inch = Growth / Inch_sm;
    std::cout << "Height in inches: " << Growth_inch << std::endl;

    int f = int (Growth_inch) / Foot_inch;
    int d = int (Growth_inch) % Foot_inch;
    std::cout << "Your height: " << f << " foot " << d << " inch" << std::endl;

    return 0;
}
