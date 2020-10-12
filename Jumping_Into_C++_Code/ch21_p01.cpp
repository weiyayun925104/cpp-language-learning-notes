#include <cmath>
#include <iostream>
#include <string>
#include "calculator.h"

using namespace std;

double add(double left, double right)
{
    return (left + right);
}

double subtract(double left, double right)
{
    return (left - right);
}

double multiply(double left, double right)
{
    return (left * right);
}

double divide(double left, double right)
{
    if (right == 0)
    {
        return INFINITY;
    }
    return (left / right);
}

int main()
{
    while (true)
    {
        int choice = 0;
        bool isValidChoice = false;
        while (!isValidChoice)
        {
            choice = 0;

            cout << "Choose from the following operations:\n";
            cout << "0. Exit\n";
            cout << "1. Add\n";
            cout << "2. Subtract\n";
            cout << "3. Multiply\n";
            cout << "4. Divide\n";
            cin >> choice;
            cin.clear();
            cin.ignore(80, '\n');

            if (choice == 0)
            {
                return 0;
            }
            isValidChoice = (0 <= choice && choice <= 4);
            if (!isValidChoice)
            {
                cout << "Please enter a valid number.\n";
            }
            cout << '\n';
        }

        double left = 0;
        cout << "Left-hand side value: ";
        cin >> left;
        cin.clear();
        cin.ignore(80, '\n');
        cout << '\n';

        double right = 0;
        cout << "Right-hand side value: ";
        cin >> right;
        cin.clear();
        cin.ignore(80, '\n');
        cout << '\n';

        double result;
        string operatorSymbol;
        switch (choice)
        {
        case 1:
            result = add(left, right);
            operatorSymbol = "+";
            break;
        case 2:
            result = subtract(left, right);
            operatorSymbol = "-";
            break;
        case 3:
            result = multiply(left, right);
            operatorSymbol = "*";
            break;
        case 4:
            result = divide(left, right);
            operatorSymbol = "/";
            break;
        default:
            result = add(left, right);
            operatorSymbol = "+";
            break;
        }
        cout << left << " " << operatorSymbol << " " << right << " = " << result << "\n\n";
    }
}
