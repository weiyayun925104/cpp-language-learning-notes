#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


vector<string> GetInput()
{
    string word;
    vector<string> words;

    cout << "Please enter some words:" << endl;

    while (cin >> word)
    {
        words.push_back(word);
    }

    return words;
}

int LongestShortestString(const vector<string> &words)
{

    if (words.size() < 1)
    {
        cout << "Please enter atleast 1 words." << endl;
        return 1;
    }

    vector<string>::size_type shortest, longest;
    shortest = longest = words[0].size();

    for (vector<string>::size_type i = 1; i < words.size(); i++)
    {
        if (words[i].size() < shortest)
        {
            shortest = words[i].size();
        }
        if (words[i].size() > longest)
        {
            longest = words[i].size();
        }
    }

    cout << "The shortest word is " << shortest << " characters long." << endl
         << "The longest word is " << longest << " characters long." << endl;

    return 0;
}

int main()
{
    return LongestShortestString(GetInput());
}
