#include <iostream>
#include <array>

int main()
{
    std::array<double, 3> result;

    std::cout << "Enter 3 race results: " << std::endl;
    std::cin >> result[0] >> result[1] >> result[2];

    std::cout << "You typed: ";
    std::cout << result[0] << ", " << result[1] << ", " << result[2] << std::endl;

    std::cout << "Average value: ";
    double Average = (result[0] + result[1] + result[2]) / 3.0;
    std::cout << Average << std::endl;

    return 0;
}
