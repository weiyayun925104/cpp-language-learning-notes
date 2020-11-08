#include <iostream>

using namespace std;

int main()
{
    char ch;
    int count = 0;
    cin.get(ch);
    while (cin.eof() == false)
    {
        cout << ch;
        ++count;
        cin.get(ch);
    }
    cout << '\n' << count << " characters read.\n";

    return 0;
}
