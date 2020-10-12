#include <iostream>
#include <string>

using namespace std;

int main()
{
    string operation;
    double number1 = 0;
    double number2 = 0;
    double result = 0;

    cout << "Please enter one of the four arithmetic operators: +, -, *, /" << "\n";
    cin >> operation;

    if ( ! ( (operation == "+") || (operation == "-") || (operation == "*") || (operation == "/") ) )
    {
        cout << "You entered an invalid operator! Program will exit." << "\n";
        return 0;
    }

    cout << "Please enter two numbers to use with the operator.\nNumber1: ";
    cin >> number1;
    cout << "Number2: ";
    cin >> number2;

    if (operation == "+")
    {
        result = number1 + number2;
    }
    else if (operation == "-")
    {
        result = number1 - number2;
    }
    else if (operation == "*")
    {
        result = number1 * number2;
    }
    else if (operation == "/")
    {
        if (number2 == 0)
        {
            cout << "Denominator is 0! Result is infinity.";
            return 0;
        }
        result = number1 / number2;
    }

    cout << "Operation is: \n" << number1 << " " << operation << " " << number2 << " = " << result << "\n";
}
