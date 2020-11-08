#include <iostream>

double Multiplication(double x, double y);
double Division(double x, double y);
double Subtraction(double x, double y);
double Addition(double x, double y);
double Calculate(double x, double y, double (*pf)(double x, double y));
void print_menu();

int main()
{
    print_menu();
    int menu = 0;
    while (std::cin >> menu)
    {
        double x = 0, y = 0;
        switch (menu)
        {
        case 1:
            std::cout << "Enter x and y : ";
            std::cin >> x >> y;
            std::cout << x << " * " << y << " = " << Calculate(x, y, Multiplication) << std::endl;
            break;
        case 2:
            std::cout << "Enter x and y : ";
            std::cin >> x >> y;
            std::cout << x << " / " << y << " = " << Calculate(x, y, Division) << std::endl;
            break;
        case 3:
            std::cout << "Enter x and y : ";
            std::cin >> x >> y;
            std::cout << x << " - " << y << " = " << Calculate(x, y, Subtraction) << std::endl;
            break;
        case 4:
            std::cout << "Enter x and y : ";
            std::cin >> x >> y;
            std::cout << x << " + " << y << " = " << Calculate(x, y, Addition) << std::endl;
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            break;
        }
        print_menu();
        menu = 0;
    }

    return 0;
}

double Multiplication(double x, double y)
{
    return x * y;
}

double Division(double x, double y)
{
    return x / y;
}

double Subtraction(double x, double y)
{
    return x - y;
}

double Addition(double x, double y)
{
    return x + y;
}

double Calculate(double x, double y, double(*pf)(double x, double y))
{
    return (*pf)(x, y);
}

void print_menu()
{
    std::cout << "Choose the action of the calculator: " << std::endl;
    std::cout << "[1] - Multiplication: " << std::endl;
    std::cout << "[2] - Division: " << std::endl;
    std::cout << "[3] - Subtraction: " << std::endl;
    std::cout << "[4] - Addition: " << std::endl;
    std::cout << "[q] - Quit: " << std::endl;
}
