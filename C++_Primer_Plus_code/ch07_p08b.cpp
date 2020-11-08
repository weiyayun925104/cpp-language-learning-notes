#include <iostream>
#include <array>
#include <string>

const int Seasons = 4;

const char Snames[][8] =
{
    "Spring", "Summer", "Fall", "Winter"
};

struct Expenses
{
    double expenses[Seasons];
};

void fill(const char Snames[][8], Expenses *exp);
void show(const char Snames[][8], Expenses *exp);

int main()
{
    Expenses exp;
    fill(Snames, &exp);
    show(Snames, &exp);

    return 0;
}

void fill(const char Snames[][8], Expenses *exp)
{
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << "Enter " << Snames[i] << " expenses: ";
        std::cin >> exp->expenses[i];
    }
}

void show(const char Snames[][8], Expenses *exp)
{
    double total = 0.0;
    std::cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << Snames[i] << ": $" << exp->expenses[i] <<  std::endl;
        total += exp->expenses[i];
    }
    std::cout << "Total Expenses: $" << total <<  std::endl;
}
