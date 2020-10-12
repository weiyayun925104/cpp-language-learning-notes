#pragma once
#ifndef REVERSESORT_H_
#define REVERSESORT_H_

#include <string>
#include "Comparator.h"

using namespace std;

class ReverseSort : public Comparator
{
public:
    virtual ~ReverseSort();
    virtual int compare(const string &lhs, const string &rhs);
};

#endif
