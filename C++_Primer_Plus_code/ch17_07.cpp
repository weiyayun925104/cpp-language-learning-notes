#include <iostream>
#include <iomanip>

int main()
{
    using namespace std;
    char name[20];
    double hourly;
    double hours;

    cout << "Enter your name: ";
    cin.get(name,20).get();
    cout << "Enter your hourly wages: ";
    cin >> hourly;
    cout << "Enter number of hours worked: ";
    cin >> hours;

    cout << showpoint << fixed << right;
    cout << "First format: \n";
    cout << setw(30) << name << ": $" << setprecision(2)
            << setw(10) << hourly << ":" << setprecision(1)
            << setw(5) << hours << "\n";
    cout << "Second format: \n";
    cout << left;
    cout << setw(30) << name << ": $" << setprecision(2)
            << setw(10) << hourly << ":" << setprecision(1)
            << setw(5) << hours << "\n";

    return 0;
}