#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename Type>
int compare(const Type &itemA, const Type &itemB)
{
    if (itemA < itemB)
    {
        return -1;
    }
    else if (itemA > itemB)
    {
        return 1;
    }
    return 0;
}

template <typename Type>
int getMinElementIndex(const vector<Type> &vectorToSearch)
{
    int minElementIndex = 0;
    Type minElement = vectorToSearch[0];
    int vectorSize = vectorToSearch.size();
    for (int i = 0; i < vectorSize; i++)
    {
        int compareResult = compare(vectorToSearch[i], minElement);
        if (compareResult == -1)
        {
            minElement = vectorToSearch[i];
            minElementIndex = i;
        }
    }
    return minElementIndex;
}

template <typename Type>
vector<Type> sortVector(const vector<Type> &vectorToSort)
{
    vector<Type> sortedVector;
    vector<Type> unsortedVector(vectorToSort);
    while (unsortedVector.size() != 0)
    {
        int minElementIndex = getMinElementIndex(unsortedVector);
        sortedVector.push_back(unsortedVector[minElementIndex]);
        unsortedVector.erase(unsortedVector.begin() + minElementIndex);
    }
    return sortedVector;
}

int main()
{
    vector<int> vectorInt;

    vectorInt.push_back(2);
    vectorInt.push_back(5);
    vectorInt.push_back(4);
    vectorInt.push_back(3);
    vectorInt.push_back(0);
    vectorInt.push_back(1);

    cout << "Integer type:\n";
    for (int i = 0; i < vectorInt.size(); i++)
    {
        cout << vectorInt[i] << '\n';
    }
    cout << endl;

    cout << "Sorting Vector:\n";
    vector<int> vectorIntSorted = sortVector(vectorInt);
    for (int i = 0; i < vectorIntSorted.size(); i++)
    {
        cout << vectorIntSorted[i] << '\n';
    }
    cout << endl;

    vector<double> vectorDbl;

    vectorDbl.push_back(1.1);
    vectorDbl.push_back(5.5);
    vectorDbl.push_back(2.2);
    vectorDbl.push_back(0);
    vectorDbl.push_back(4.4);
    vectorDbl.push_back(3.3);
    cout << "Double type:\n";

    for (int i = 0; i < vectorDbl.size(); i++)
    {
        cout << vectorDbl[i] << '\n';
    }
    cout << endl;

    cout << "Sorting Vector:\n";
    vector<double> vectorDblSorted = sortVector(vectorDbl);
    for (int i = 0; i < vectorDblSorted.size(); i++)
    {
        cout << vectorDblSorted[i] << '\n';
    }
    cout << endl;

    vector<string> vectorStr;

    vectorStr.push_back("Value = 2.2");
    vectorStr.push_back("Value = 5.5");
    vectorStr.push_back("Value = 4.4");
    vectorStr.push_back("Foo");
    vectorStr.push_back("Value = 3.3");
    vectorStr.push_back("Value = 1.1");
    vectorStr.push_back("Value = 0");
    vectorStr.push_back("Bar");
    cout << "String type:\n";
    for (int i = 0; i < vectorStr.size(); i++)
    {
        cout << vectorStr[i] << '\n';
    }
    cout << endl;

    cout << "Sorting Vector:\n";
    vector<string> vectorStrSorted = sortVector(vectorStr);
    for (int i = 0; i < vectorStrSorted.size(); i++)
    {
        cout << vectorStrSorted[i] << '\n';
    }
    cout << endl;
}
