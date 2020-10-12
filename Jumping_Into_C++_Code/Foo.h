#pragma once
#ifndef FOO_H_
#define FOO_H_

#include <string>
#include "StringConvertable.h"

using namespace std;

class Foo : public StringConvertable
{
public:
    virtual ~Foo();
    virtual string toString();
};

#endif
