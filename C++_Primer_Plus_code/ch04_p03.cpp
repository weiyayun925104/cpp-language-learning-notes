#include <iostream>
#include <cstring>

int main()
{
    std::cout << "What is your first name? ";
    char first_name[128];
    std::cin.getline(first_name, 128);

    std::cout << "What is your last name? ";
    char last_name[128];
    std::cin.getline(last_name, 128);

    char result[256];
    strcpy(result, last_name);
    strcat(result, ", ");
    strcat(result, first_name);
    std::cout << "Here's the information in a single string: " << result << std::endl;

    return 0;
}
