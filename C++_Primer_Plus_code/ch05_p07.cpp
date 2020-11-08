#include <iostream>
#include <string>

struct car
{
    std::string name;
    int age;
};

int main()
{
    std::cout << "Enter the number of machines that you want to catalog: ";
    int array_count;
    (std::cin >> array_count).get();

    car *ptr = new car[array_count];
    for (int i = 0; i < array_count; i++)
    {
        std::cout << "Car " << i + 1 << std::endl;
        std::cout << "Enter the manufacturer: ";
        std::getline(std::cin, ptr[i].name, '\n');
        std::cout << "Please enter the year of manufacture: ";
        (std::cin >> ptr[i].age).get();
    }

    std::cout << "Here is your collection:" << std::endl;

    for (int j = 0; j < array_count; j++)
    {
        std::cout << ptr[j].age << " : " << ptr[j].name << std::endl;
    }
    delete[] ptr;

    return 0;
}
