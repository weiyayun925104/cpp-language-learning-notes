#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cout << setfill( '-' ) << setw( 10 ) << "ten" << endl;
    cout << setfill( '-' ) << setw( 10 ) << "ten" << "four" << "four" << endl;
    cout << setfill( ' ' ) << setw( 10 ) << left << "ten" << "four" << "four" << endl;
    const char last_fill = cout.fill( '-' );
    cout << setw( 10 ) << right << "A" << setw( 10 ) << "B" << setw( 10 ) << "C" << endl;
    cout.fill( last_fill );
    cout << setw( 10 ) << "D" << endl;
}
