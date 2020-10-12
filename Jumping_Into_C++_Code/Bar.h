#pragma once
#ifndef BAR_H_
#define BAR_H_

#include <string>
#include "StringConvertable.h"

using namespace std;

class Bar : public StringConvertable
{
public:
    virtual ~Bar();
    virtual string toString();
};

#endif
