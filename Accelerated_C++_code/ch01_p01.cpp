#include <iostream>
#include <string>

int main()
{
    const std::string hello = "Hello";
    const std::string message = hello + ", world" + "!";

    std::cout << hello << '\n';
    std::cout << message << '\n';

    return 0;
}
