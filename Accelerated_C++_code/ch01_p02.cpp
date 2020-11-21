#include <iostream>
#include <string>

int main()
{
    const std::string exclam = "!";
    const std::string message = "Hello" + (", world" + exclam);

    std::cout << exclam << '\n';
    std::cout << message << '\n';

    return 0;
}
