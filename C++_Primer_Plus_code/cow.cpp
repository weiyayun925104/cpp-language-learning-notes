#include <iostream>
#include <cstring>
#include "cow.h"

Cow::Cow()
{
    std::cout << "Default constructor called" << std::endl;

    name[0] = '\0';
    hobby = new char[1];
    hobby[0] = '\0';
    weight = 0;
}

Cow::Cow(const char *nm, const char *ho, double wt)
{
    std::cout << "Constructor with parameters was called" << std::endl;

    strncpy(name, nm, 20);
    hobby = new char[strlen(ho) + 1];
    strcpy(hobby, ho);
    weight = wt;
}

Cow::Cow(const Cow &c)
{
    std::cout << "Copy Constructor called" << std::endl;

    strncpy(name, c.name, 20);
    hobby = new char[strlen(c.hobby) + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;
}

Cow::~Cow()
{
    std::cout << name << " Called the destructor" << std::endl;

    delete[] hobby;
}

Cow &Cow::operator = (const Cow &c)
{
    std::cout << "Assignment operator called" << std::endl;

    if (this == &c)
    {
        return *this;
    }
    delete[] hobby;

    strncpy(name, c.name, 20);
    hobby = new char[strlen(c.hobby) + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;

    return *this;
}
ostream &operator<<(ostream &os, const Cow &c)
{
    os << "Name: " << c.name << '\n';
    os << "Hobby: " << c.hobby << '\n';
    os << "Weight: " << c.weight << "\n\n";
    return os;
}
