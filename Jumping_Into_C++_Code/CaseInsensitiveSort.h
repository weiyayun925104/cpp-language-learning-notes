#pragma once
#ifndef CASEINSENSITIVESORT_H_
#define CASEINSENSITIVESORT_H_

#include <string>
#include "Comparator.h"

using namespace std;

class CaseInsensitiveSort : public Comparator
{
public:
    virtual ~CaseInsensitiveSort();
    virtual int compare(const string &lhs, const string &rhs);
};

#endif
