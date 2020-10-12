#include <iostream>
#include <string>

using namespace std;

int main()
{
    for (int beer = 99; beer > 0; beer--)
    {
        if(beer != 99)
        {
            cout << beer << " bottles of beer on the wall.\n";
        }
        cout << beer << " bottles of beer on the wall, " << beer << " bottles of beer.\n" <<
             "Take one down, pass it around...\n";
    }
}
