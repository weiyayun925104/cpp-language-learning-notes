#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cout << setw( 10 ) << "ten" << endl;
    cout << setw( 10 ) << "ten" << "four" << "four"<< endl;
    cout << setw( 10 ) << left << "ten" << "four" << "four"<< endl;
}
