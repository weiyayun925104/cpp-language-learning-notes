#include <iostream>

int main()
{
    std::cout << "What is your first name? ";
    char first_name[128];
    std::cin.getline(first_name, 128);

    std::cout << "What is your last name? ";
    char last_name[128];
    std::cin.getline(last_name, 128);

    std::cout << "What letter grade do you deserve? ";
    char ctg;
    std::cin >> ctg;
    ctg = ctg + 1;

    std::cout << "What is your age? ";
    int age = 0;
    std::cin >> age;

    std::cout << "Name: " << last_name << ", " << first_name << std::endl;
    std::cout << "Grade: " << ctg << std::endl;
    std::cout << "Age: " << age << std::endl;

    return 0;
}
