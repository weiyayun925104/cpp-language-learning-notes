#include <iostream>

int main()
{
    double daphne = 100;
    double cleo = 100;
    int age = 0;

    std::cout << "Balance Daphne: " << daphne << std::endl;
    std::cout << "Balance Cleo: " << cleo << std::endl;
    std::cout << std::endl;

    do
    {
        daphne += 0.10 * 100;
        cleo += 0.05 * cleo;
        age++;

        std::cout << "Balance Daphne: " << daphne << std::endl;
        std::cout << "Balance Cleo: " << cleo << std::endl;
        std::cout << "Years passed: " << age << std::endl;

        std::cout << std::endl;
    }
    while (cleo <= daphne);

    return 0;
}
