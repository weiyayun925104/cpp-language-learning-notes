#include <iostream>

using namespace std;

char *buildstr(char c, int n);

int main()
{
    char ch;
    cout << "Enter a character: ";
    cin.get(ch);
    while (cin.get() != '\n')
    {
        continue;
    }
    cout << "Enter an integer: ";
    int times = 0;
    if ( ! (cin >> times) || times <= 0)
    {
        return 0;
    }
    char *ps = buildstr(ch, times);
    cout << ps << endl;
    delete [] ps;
    ps = buildstr('+', 20);
    cout << ps << endl;
    delete [] ps;

    return 0;
}

char *buildstr(char c, int n)
{
    char *pstr = new char[n + 1];
    pstr[n] = '\0';
    while (n-- > 0)
    {
        pstr[n] = c;
    }
    return pstr;
}
