#include <iostream>
#include <string>

int main()
{
    std::cout << "What is your first name? ";
    std::string first_name;
    std::getline(std::cin, first_name, '\n');

    std::cout << "What is your last name? ";
    std::string last_name;
    std::getline(std::cin, last_name, '\n');

    std::string result;
    result = last_name + ", " + first_name;
    std::cout << "Here's the information in a single string: " << result << std::endl;

    return 0;
}
