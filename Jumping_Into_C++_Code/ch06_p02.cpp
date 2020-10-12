
#include <iostream>
#include <string>

using namespace std;

double Add(double number1, double number2);
double Subtract(double number1, double number2);
double Multiply(double number1, double number2);
double Divide(double number1, double number2);

int main()
{
    string operation;
    double number1 = 0;
    double number2 = 0;
    double result = 0;

    cout << "Please enter one of the four arithmetic operators: +, -, *, /" << "\n";
    cin >> operation;

    if ( !( (operation == "+") ||
             (operation == "-") ||
             (operation == "*") ||
             (operation == "/") ) )
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
        result = Add(number1, number2);
    }
    else if (operation == "-")
    {
        result = Subtract(number1, number2);
    }
    else if (operation == "*")
    {
        result = Multiply(number1, number2);
    }
    else if (operation == "/")
    {
        if (number2 == 0)
        {
            cout << "Denominator is 0! Result is infinity.";
            return 0;
        }
        result = Divide(number1, number2);
    }

    cout << "Operation is: \n" <<
         number1 << " " << operation << " " << number2 << " = " << result << "\n";
}

double Add(double number1, double number2)
{
    return number1 + number2;
}

double Subtract(double number1, double number2)
{
    return number1 - number2;
}

double Multiply(double number1, double number2)
{
    return number1 * number2;
}

double Divide(double number1, double number2)
{
    return number1 / number2;
}
