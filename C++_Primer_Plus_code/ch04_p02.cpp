#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name, '\n');

    std::string dessert;
    std::cout << "Enter your favorite dessert: ";
    std::getline(std::cin, dessert, '\n');

    std::cout << "I have some delicious " << dessert << " for you, " << name << " .\n";

    return 0;
}
