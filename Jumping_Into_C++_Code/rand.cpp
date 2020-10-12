#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main ()
{
    srand( time( NULL ) );
    cout << rand() << '\n';
}
