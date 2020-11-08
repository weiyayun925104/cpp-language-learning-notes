#include <iostream>
#include <string>

struct CandyBar
{
    std::string candy_name;
    double weight;
    int calories;
};

int main()
{
    CandyBar snack;
    snack.candy_name = "Mocha Munch";
    snack.weight = 2.3;
    snack.calories= 350;

    std::cout << "Name: " << snack.candy_name << std::endl;
    std::cout << "Weight: " << snack.weight << std::endl;
    std::cout << "Calories: " << snack.calories << std::endl;

    return 0;
}
