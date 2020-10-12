
#include <iostream>
#include <string>

using namespace std;

int numberOfNeedlesInHaystack(const string &haystack, const string &needle);

int main()
{
    string needle;
    cout << "Please enter a line of text to find: "<<endl;
    getline(cin, needle, '\n');

    string haystack;
    cout << "Please enter a line of text to search for the number of occurrences: "<<endl;
    getline(cin, haystack, '\n');

    int needleAppearances = numberOfNeedlesInHaystack(needle, haystack);
    cout << "The word " << needle << " appears " << needleAppearances << " in the string " << haystack << endl;
}

int numberOfNeedlesInHaystack(const string &needle, const string &haystack)
{
    int i = 0;
    int needleAppearances = 0;

    for (i = haystack.find(needle, 0); i != string::npos; i = haystack.find(needle, i))
    {
        needleAppearances++;
        i++;
    }
    return needleAppearances;
}
