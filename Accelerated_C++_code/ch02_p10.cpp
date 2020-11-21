#include <iostream>

const int n = 5;

int main()
{
    int k = 0;
    while (k != n)
    {
        using std::cout;   // the using statement is only relevant to the local while scope
        cout << "*";
        ++k;
    }
    std::cout << std::endl;   // std:: is required here
    return 0;
}
