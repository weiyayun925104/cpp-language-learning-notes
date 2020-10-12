#include <iostream>

using namespace std;

int *growArray (int *p_values, int cur_size);

int main ()
{
    int next_element = 0;
    int size = 10;
    int *p_values = new int [ size ];
    int val = 0;
    cout << "Please enter a positive number (0 to exit): ";
    cin >> val;
    while ( val > 0 )
    {
        if ( size == next_element )
        {
            p_values = growArray( p_values, size );
        }
        p_values[ next_element ] = val;
        next_element++;
        val = 0;
        cout << "Please enter a positive number (0 to exit): ";
        cin >> val;
    }
    for (int i = 0; i < next_element; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << p_values[ i ];
    }
    delete [] p_values;
}
int *growArray (int *p_values, int cur_size)
{
    int *p_new_values = new int[ cur_size * 2 ];
    for ( int i = 0; i < cur_size; ++i )
    {
        p_new_values[ i ] = p_values[ i ];
    }
    delete [] p_values;
    return p_new_values;
}
