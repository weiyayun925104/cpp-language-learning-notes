#include <iostream>
#include <string>

int main()
{
    std::string dot = ".";
    std::string star = "*";

    std::cout << "Enter the number of rows: ";
    int count = 0;
    std::cin >> count;

    if (count <= 0)
    {
        return 0;
    }

    for (int i = 1; i <= count; i++)
    {
        for (int j = 0; j < count - i; j++)
        {
            std::cout << dot;
        }
        for (int j = 0; j < i; j++)
        {
            std::cout << star;
        }
        std::cout << std::endl;
    }

    return 0;
}
