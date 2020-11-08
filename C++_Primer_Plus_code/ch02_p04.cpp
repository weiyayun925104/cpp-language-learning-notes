#include <iostream>

int age_months(int age);

int main()
{
    std::cout << "Enter your age: ";

    int age = 0;
    std::cin >> age;

    std::cout << "Your age in months is " << age_months(age) << std::endl;

    return 0;
}

int age_months(int age)
{
    return age * 12;
}
