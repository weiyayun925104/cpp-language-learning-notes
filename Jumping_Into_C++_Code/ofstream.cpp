#include <fstream>
#include <iostream>

using namespace std;

int main ()
{
    ofstream file_writer( "highscores.txt" );
    if ( ! file_writer.is_open() )
    {
        cout << "Could not open file!" << '\n';
        return 0;
    }

    for ( int i = 0; i < 10; i++ )
    {
        file_writer << 10 - i << '\n';
    }
}
