
#include <iostream>

int main()
{
    std::cout << "Enter the number of frolongs " << std::endl;

    int frolong = 0;
    std::cin >> frolong;

    int yard = frolong * 220;
    std::cout << frolong << " Frolong = " << yard << " yard" << std::endl;

    return 0;
}
