#include <iostream>
#include <string>
#include "ReverseSort.h"

using namespace std;

ReverseSort::~ReverseSort()
{
    cout << "ReverseSort's destructor\n";
}

int ReverseSort::compare(const string &lhs, const string &rhs)
{
    if (lhs < rhs)
    {
        return -1;
    }
    else if (lhs > rhs)
    {
        return 1;
    }
    return 0;
}
