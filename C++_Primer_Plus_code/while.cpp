#include <iostream>
#include <string>

using namespace std;

const int ArSize = 128;

int main()
{
    char name[ArSize];

    cout << "Please enter your name: ";
    cin.getline(name, ArSize);

    cout << "Here is your name: \n";
    int i = 0;
    while (name[i] != '\0')
    {
        cout << name[i] << ": " << int (name[i]) << endl;
        i++;
    }

    return 0;
}
