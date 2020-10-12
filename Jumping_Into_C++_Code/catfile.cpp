#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{

    if ( argc != 2 )
    {
        cout << "usage: " << argv[ 0 ] << " <filename>" << endl;
    }
    else
    {
        ifstream the_file( argv[ 1 ] );
        if ( ! the_file.is_open() )
        {
            cout << "Could not open file " << argv[ 1 ] << endl;
            return 1;
        }
        char x;
        while ( the_file.get( x ) )
        {
            cout << x;
        }
    }
}
