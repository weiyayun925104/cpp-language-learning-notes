#include <cstdlib>
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
    if ( argc != 2 )
    {
        cout << "usage: " << argv[ 0 ] << " <number>" << endl;
    }
    else
    {
        int val = atoi(argv[1]);
        cout << val *val;
    }
    return 0;
}
