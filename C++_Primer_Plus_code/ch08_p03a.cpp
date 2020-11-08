#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int main()
{
    string s = "Hello World";
    cout << s << endl;
    transform(s.begin(),s.end(),s.begin(),::toupper);
    cout << s << endl;
    transform(s.begin(),s.end(),s.begin(),::tolower);
    cout << s << endl;

    return 0;
}
