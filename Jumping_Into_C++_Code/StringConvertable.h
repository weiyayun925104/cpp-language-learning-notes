#pragma once
#ifndef STRINGCONVERTABLE_H_
#define STRINGCONVERTABLE_H_

#include <string>

using namespace std;

class StringConvertable
{
public:
    virtual ~StringConvertable();
    virtual string toString() = 0;
};

#endif
