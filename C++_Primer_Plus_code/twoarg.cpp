#include <iostream>

using namespace std;

void n_chars(char, int);

int main()
{
    int times;
    char ch;
    cout << "Enter a character: ";
    cin.get(ch);
    while (cin.get() != '\n')
    {
        continue;
    }
    while (ch != 'q')
    {
        cout << "Enter an integer: ";
        times = 0;
        if ( ! (cin >> times) )
        {
            break;
        }
        while (cin.get() != '\n')
        {
            continue;
        }
        n_chars(ch, times);
        cout << "\ntimes = " << times << ".\n";
        cout << "Enter a character (q to quit) : ";
        cin.get(ch);
        while (cin.get() != '\n')
        {
            continue;
        }
    }
    cout << "Done.\n";

    return 0;
}

void n_chars(char c, int n)
{
    while (n-- > 0)
    {
        cout << c;
    }
}
