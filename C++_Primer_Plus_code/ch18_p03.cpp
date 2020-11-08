#include <iostream>
#include <iomanip>

long double sum_values()
{
    return 0.0;
}

template <typename T, typename ... Args>
long double sum_values(const T &value, const Args &... args)
{
    long double sum = 0;
    sum = value + sum_values(args ...);
    return sum;
}

int main()
{
    std::cout << std::fixed;
    std::cout << sum_values(5, 5, 5) << std::endl;
    std::cout << std::setprecision(10) << sum_values(20.0, 1.0, 8.6578787879, 1) << std::endl;

    return 0;
}
