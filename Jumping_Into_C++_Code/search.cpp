#include <iostream>
#include <string>

using namespace std;

int main ()
{
    string input;
    int i = 0;
    int cat_appearances = 0;

    cout << "Please enter a line of text: ";
    getline( cin, input, '\n' );

    for ( i = input.find( "cat", 0 ); i != string::npos; i = input.find( "cat", i ) )
    {
        cat_appearances++;
        i++;
    }
    cout << "The word cat appears " << cat_appearances << " in the string " << input << '\n';
}
