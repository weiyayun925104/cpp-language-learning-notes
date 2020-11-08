#include <iostream>
#include <string>

using namespace std;

string version1(const string &si, const string &s2);
const string &version2(string &si, const string &s2);
const string version3(string &si, const string &s2);

int main()
{
    string input;
    string copy;
    string result;
    cout << "Enter a string: ";
    getline(cin, input, '\n');
    copy = input;
    cout << "Your string as entered: " << input << endl;
    result = version1(input, "***");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    result = version2(input, "###");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    cout << "Resetting original string.\n";
    input = copy;
    result = version3(input, "@@@");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    return 0;
}

string version1(const string &si, const string &s2)
{
    string temp;
    temp = s2 + si + s2;
    return temp;
}

const string &version2(string &si, const string &s2)
{
    si = s2 + si + s2;
    return si;
}

const string version3(string &si, const string &s2)
{
    string temp;
    temp = s2 + si + s2;
    return temp;
}
