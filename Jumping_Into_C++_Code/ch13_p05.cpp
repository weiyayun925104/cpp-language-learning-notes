#include <iostream>
#include <string>

using namespace std;

int main()
{
    int number = 50;
    int *numberAddress = &number;
    int numberValue = number;
    cout << "Number variable has the following\n";
    cout << "Address: " << numberAddress << " Value: " << numberValue << '\n';

    int number2 = 1;
    int *numberAddress2 = &number2;
    int numberValue2 = number2;
    cout << "Number variable has the following\n";
    cout << "Address: " << numberAddress2 << " Value: " << numberValue2 << '\n';

    cout << '\n';
    cout << "Variables will be written in order of their addresses: \n";
    if (numberAddress2 < numberAddress)
    {
        cout << "Address: " << numberAddress2 << " Value: " << numberValue2 << '\n';
        cout << "Address: " << numberAddress << " Value: " << numberValue << '\n';
    }
    else
    {
        cout << "Address: " << numberAddress << " Value: " << numberValue << '\n';
        cout << "Address: " << numberAddress2 << " Value: " << numberValue2 << '\n';
    }
    cout << "\n\n";

    string name = "Mark";
    string *nameAddress = &name;
    string nameValue = name;

    cout << "Name variable has the following\n";
    cout << "Address: " << nameAddress << " Value: " << nameValue << '\n';

    string name2 = "Rutherfurd";
    string *nameAddress2 = &name2;
    string nameValue2 = name2;

    cout << "Name variable has the following\n";
    cout << "Address: " << nameAddress2 << " Value: " << nameValue2 << '\n';

    cout << '\n';
    cout << "Variables will be written in order of their addresses: \n";
    if (nameAddress2 < nameAddress)
    {
        cout << "Address: " << nameAddress2 << " Value: " << nameValue2 << '\n';
        cout << "Address: " << nameAddress << " Value: " << nameValue << '\n';
    }
    else
    {
        cout << "Address: " << nameAddress << " Value: " << nameValue << '\n';
        cout << "Address: " << nameAddress2 << " Value: " << nameValue2 << '\n';
    }
}
