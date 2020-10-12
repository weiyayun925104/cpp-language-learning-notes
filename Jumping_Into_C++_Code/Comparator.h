#pragma once
#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include<string>

using namespace std;

class Comparator
{
public:
    virtual ~Comparator();
    virtual int compare(const string &lhs, const string &rhs) = 0;
};

#endif
