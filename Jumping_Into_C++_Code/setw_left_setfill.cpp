#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cout << setfill( '-' )<< setw( 10 ) << "ten" << endl;
    cout << setfill( '-' )<< setw( 10 ) << "ten" << "four" << "four"<< endl;
    cout << setfill( '-' )<< setw( 10 ) << left << "ten" << "four" << "four"<< endl;
}
