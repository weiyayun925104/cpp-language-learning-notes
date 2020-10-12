#include <iostream>

using namespace std;

int main ()
{
    int votes[ 10 ];

    for ( int i = 0; i < 10; ++i )
    {
        votes[ i ] = 0;
    }

    int candidate = 0;
    cout << "Vote for the candidate of your choice, Plese enter a number (1-10): \n";
    cout << "1) Joe 2) Bob 3) Mary 4) Suzy 5) Margaret 6) Eleanor 7) Alex 8) Thomas 8) Andrew 10) Ilene\n";
    cin >> candidate;

    while ( 1 <= candidate && candidate <= 10 )
    {
        votes[ candidate-1 ]++;
        candidate = 0;
        cout << "Vote for the candidate of your choice, Plese enter a number (1-10): \n";
        cout << "1) Joe 2) Bob 3) Mary 4) Suzy 5) Margaret 6) Eleanor 7) Alex 8) Thomas 8) Andrew 10) Ilene\n";
        cin >> candidate;
    }
    cout << "\n\n";
    for ( int i = 0; i < 10; ++i )
    {
        cout << votes[ i ] << '\n';
    }
}
