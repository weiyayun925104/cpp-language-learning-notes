#include <iostream>

int main()
{
    std::cout << "Enter a and b: ";
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    if (a > b)
    {
        return 0;
    }
    int result = 0;
    for (int i = a; i <= b; i++)
    {
        result += i;
    }
    std::cout << "Result: " << result << std::endl;

    return 0;
}
