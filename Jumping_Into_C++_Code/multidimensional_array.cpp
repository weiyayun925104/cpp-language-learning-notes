#include <iostream>

using namespace std;

int main ()
{
    int array[ 8 ][ 8 ];

    for ( int i = 0; i < 8; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            array[ i ][ j ] = i * j;
        }
    }
    cout << "Multiplication table:\n";
    for ( int i = 0; i < 8; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            cout << "[ " << i << " ][ " << j << " ] = ";
            cout << array[ i ][ j ] << " ";
            cout << "\n";
        }
    }
}
