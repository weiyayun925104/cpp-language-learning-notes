#include <iostream>
#include <string>

using namespace std;

int main()
{
    double sum = 0.0;
    double inputValue = 0.0;

    do
    {
        cout << "Please provide a number to add to the sum of " << sum << "\n";
        cin >> inputValue;
        sum += inputValue;
    }
    while (inputValue != 0.0);
}
