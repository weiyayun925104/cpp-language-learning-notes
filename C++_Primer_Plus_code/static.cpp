#include <iostream>

using namespace std;

const int ArSize = 128;

void strcount(const char *str);

int main()
{
    char input[ArSize];
    char next;

    cout << "Enter a line:\n";
    while ( cin.get(input, ArSize) )
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        strcount(input);
        cout << "Enter a line:\n";
    }
    cout << "Done.\n";

    return 0;
}
void strcount(const char *str)
{
    static int total = 0;
    int count = 0;
    cout << "\"" << str << "\" contains ";
    while (*str++)
    {
        count++;
    }
    total += count;
    cout << count << " characters\n";
    cout << total << " characters total\n";
}
