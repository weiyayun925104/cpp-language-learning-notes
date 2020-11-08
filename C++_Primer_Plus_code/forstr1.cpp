#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter a word: ";
    string word;
    getline(cin, word, '\n');

    for (int i = word.size() - 1; i >= 0; i--)
    {
        cout << word[i];
    }
    cout << "\nDone.\n";

    return 0;
}
