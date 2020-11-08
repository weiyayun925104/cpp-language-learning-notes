#include <iostream>
#include <cstring>
#include "person_class.h"

Person::Person(const std::string &In, const char *fn)
{
    lname = In;
    strcpy(fname, fn);
}
Person::~Person()
{
    std::cout << "Bye, " << lname << ", " << fname << "!\n";
}
void Person::Show() const
{
    std::cout << fname << " " << lname << std::endl;
}
void Person::FormalShow() const
{
    std::cout << lname << ", " << fname << std::endl;
}
