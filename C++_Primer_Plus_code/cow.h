#pragma once
#ifndef COW_H_
#define COW_H_

#include <iostream>

using std::ostream;

class Cow
{
    char name[20];
    char *hobby;
    double weight;
public:
    Cow();
    Cow(const char *nm, const char *ho, double wt);
    Cow(const Cow &c);
    ~Cow();
    Cow & operator = (const Cow & c);
    friend ostream & operator << (ostream & os, const Cow & c);
};

#endif
