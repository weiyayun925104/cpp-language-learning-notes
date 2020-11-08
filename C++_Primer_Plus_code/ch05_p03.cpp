#include <iostream>

int main()
{
    long long result = 0;
    long long a;

    do
    {
        std::cout << "Enter number: ";
        a = 0;
        std::cin >> a;
        result += a;
        std::cout << "sum = " << result << std::endl;
    }
    while (a != 0);

    return 0;
}
