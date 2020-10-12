#include <iostream>
#include <list>
#include "CaseInsensitiveSort.h"
#include "ReverseSort.h"

using namespace std;

void print(const list<string> &items);
list<string> sort(const list<string> &items, Comparator &sorter);
string getMinElement(const list<string> &items, Comparator &sorter);

int main()
{
    list<string> items;
    items.push_back("Mark");
    items.push_back("Char");
    items.push_back("Moe");
    items.push_back("Foo");
    items.push_back("maRk");
    items.push_back("Bar");
    items.push_back("Gnar");

    cout << "Creating strings added out of order...\n";
    print(items);

    cout << "Sorting string elements by case insensitive rank\n";
    CaseInsensitiveSort caseInsensitiveSorter;
    list<string> itemsSortedCaseInsensitive = sort(items, caseInsensitiveSorter);
    print(itemsSortedCaseInsensitive);

    cout << "Sorting string elements reverse alphabetical order\n";
    ReverseSort reverseSorter;
    list<string> itemsSortedReverseAlphabetical = sort(items, reverseSorter);
    print(itemsSortedReverseAlphabetical);
}

list<string> sort(const list<string> &items, Comparator &sorter)
{
    list<string> sortedScores;
    list<string> unsortedScores(items);
    while (unsortedScores.size() != 0)
    {
        string minElement = getMinElement(unsortedScores, sorter);
        sortedScores.push_front(minElement);
        unsortedScores.remove(minElement);
    }
    return sortedScores;
}


string getMinElement(const list<string> &items, Comparator &sorter)
{
    string minElement = "";
    for (list<string>::const_iterator itr = items.begin(), end = items.end(); itr != end; ++itr)
    {
        if (minElement == "")
        {
            minElement = *itr;
        }
        else if (sorter.compare(*itr, minElement) == -1)
        {
            minElement = *itr;
        }
    }
    return minElement;
}

void print(const list<string> &items)
{
    for (list<string>::const_iterator itr = items.begin(), end = items.end(); itr != end; ++itr)
    {
        cout << *itr << '\n';
    }
    cout << '\n';
}
