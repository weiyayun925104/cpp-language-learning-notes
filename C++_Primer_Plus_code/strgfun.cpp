#include <iostream>

using namespace std;

int c_in_str(const char *str, char ch);

int main()
{
    char mmm[15] = "minimum";
    const char *wail = "ululate";
    int ms = c_in_str(mmm, 'm');
    int us = c_in_str(wail, 'u');
    cout << ms << " m characters in " << mmm << endl;
    cout << us << " u characters in " << wail << endl;

    return 0;
}

int c_in_str(const char *str, char ch)
{
    int count = 0;
    while (*str)
    {
        if (*str == ch)
        {
            count++;
        }
        str++;
    }
    return count;
}
