#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter a word: ";
    string word;
    getline(cin, word, '\n');

    char temp;
    int i, j;
    for (i = 0, j = word.size() - 1; i < j; ++i, --j)
    {
        temp = word[j];
        word[j] = word[i];
        word[i] = temp;
    }
    cout << word << "\nDone\n";

    return 0;
}
