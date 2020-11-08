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
    CandyBar *snack = new CandyBar[3];

    snack[0].candy_name = "Mocha Munch";
    snack[0].weight = 1.1;
    snack[0].calories = 350;

    snack[1].candy_name = "Mocha Munch1";
    snack[1].weight = 2.2;
    snack[1].calories = 350;

    snack[2].candy_name = "Mocha Munch2";
    snack[2].weight = 3.3;
    snack[2].calories = 350;

    std::cout << "Name: " << snack[0].candy_name << std::endl;
    std::cout << "Weight: " << snack[0].weight << std::endl;
    std::cout << "Calories: " << snack[0].calories << std::endl;

    std::cout << std::endl;

    std::cout << "Name: " << snack[1].candy_name << std::endl;
    std::cout << "Weight: " << snack[1].weight << std::endl;
    std::cout << "Calories: " << snack[1].calories << std::endl;

    std::cout << std::endl;

    std::cout << "Name: " << snack[2].candy_name << std::endl;
    std::cout << "Weight: " << snack[2].weight << std::endl;
    std::cout << "Calories: " << snack[2].calories << std::endl;

    delete[] snack;

    return 0;
}
