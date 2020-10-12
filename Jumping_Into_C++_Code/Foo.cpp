#include <iostream>
#include <string>
#include "Foo.h"

using namespace std;

Foo::~Foo()
{
    cout << "Foo's destructor\n";
}

string Foo::toString()
{
    return  "Foo";
}
