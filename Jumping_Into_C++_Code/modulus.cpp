#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int randRange (int low, int high)
{
    return rand() % ( high - low + 1 ) + low;
}

int main ()
{
    int i;
    srand( time( NULL ) );

    for ( i = 0; i < 1000; ++i )
    {
        cout.width (10);
        cout.flags(ios::right);
        cout << randRange( 4, 10 );
        if (i % 8 == 7)
        {
            cout << endl;
        }
    }
    if (i % 8 != 0)
    {
        cout << endl;
    }
}
