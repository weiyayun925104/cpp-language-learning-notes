#include <iostream>
#include <string>
#include "Bar.h"

using namespace std;

Bar::~Bar()
{
    cout << "Bar's destructor\n";
}

string Bar::toString()
{
    return  "Bar";
}
