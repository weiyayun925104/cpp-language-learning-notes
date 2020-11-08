#include <iostream>
#include <string>

struct WilliamWingate
{
    std::string company_name;
    double diametr = 0.0;
    double weight = 0.0;
};

int main()
{
    WilliamWingate *Pizza = new WilliamWingate;

    std::cout << "Enter diametr: ";
    (std::cin >> Pizza->diametr).get();

    std::cout << "Enter company name: ";
    std::getline(std::cin, Pizza->company_name, '\n');

    std::cout << "Enter weight: ";
    std::cin >> Pizza->weight;

    std::cout << std::endl;

    std::cout << "Company name = " << Pizza->company_name << std::endl;
    std::cout << "Diametr = " << Pizza->diametr << std::endl;
    std::cout << "Weight = " << Pizza->weight << std::endl;

    delete Pizza;

    return 0;
}
