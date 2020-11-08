#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Please enter five numbers:\n";
    double number = 0.0;
    double sum = 0.0;
    for (int i = 1; i <= 5; i++)
    {
        cout << "Value " << i << " : ";
        cin >> number;
        sum += number;
    }

    cout << "the sum of five numbers = " << sum << endl;
    cout << "the average of five numbers = " << sum / 5 << "\n";

    return 0;
}
