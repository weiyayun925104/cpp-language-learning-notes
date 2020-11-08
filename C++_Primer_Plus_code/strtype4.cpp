#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    char charr[32] = {0};
    string str;

    cout << "Length of string in charr before input: " << strlen(charr) << endl;

    cout << "Length of string in str before input: " << str.size() << endl;

    cout << "Enter a line of text:\n";
    cin.getline(charr, 32);
    cout << "You entered: " << charr << endl;

    cout << "Enter another line of text:\n";
    getline(cin, str);
    cout << "You entered: " << str << endl;

    cout << "Length of string in charr after input: " << strlen(charr) << endl;
    cout << "Length of string in str after input: " << str.size() << endl;

    return 0;
}