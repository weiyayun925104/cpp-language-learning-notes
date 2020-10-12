#include <iostream>
#include <string>
#include "CaseInsensitiveSort.h"

using namespace std;

CaseInsensitiveSort::~CaseInsensitiveSort()
{
    cout << "CaseInsensitiveSort's destructor\n";
}

int CaseInsensitiveSort::compare(const string &lhs, const string &rhs)
{
    int lhsLength = lhs.length();
    int rhsLength = rhs.length();

    if (lhsLength == 0 && rhsLength != 0)
    {
        return -1;
    }
    else if (lhsLength != 0 && rhsLength == 0)
    {
        return 1;
    }
    else if (lhsLength == 0 && rhsLength == 0)
    {
        return 0;
    }

    char lc, rc;
    int minLength;
    lhsLength < rhsLength ? minLength = lhsLength : minLength = rhsLength;
    for (int i = 0; i < minLength; i++)
    {
        if ( ( lc = tolower(lhs[i]) ) != ( rc = tolower(rhs[i]) ) )
        {
            if (lc < rc)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }

    if (lhsLength == rhsLength)
    {
        return 0;
    }
    else if (lhsLength < rhsLength)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
