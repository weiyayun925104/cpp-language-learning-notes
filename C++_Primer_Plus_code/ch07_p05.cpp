#include <iostream>

long double factorial(int number);

int main()
{
    std::cout << "Enter any integer (0 - N): ";
    int number = 0;
    std::cin >> number;

    long double Result = factorial(number);
    std::cout << number << "! = " << Result << std::endl;

    return 0;
}

long double factorial(int number)
{
    return number > 0 ? number * factorial(number - 1) : 1;
}
