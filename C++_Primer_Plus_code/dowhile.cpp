#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cout << "Enter numbers in the range 1-10 to find my favorite number\n";
    do
    {
        cin >> n;
    }
    while (n != 7);
    cout << "Yes, 7 is my favorite. \n";

    return 0;
}
