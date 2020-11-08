#pragma once
#ifndef PERSON_CLASS_H_
#define PERSON_CLASS_H_
#include <string>

class Person
{
private:
    static const int LIMIT = 32;
    std::string lname;
    char fname[LIMIT];
public:
    Person()
    {
        lname = "";
        fname[0] = '\0';
    }
    Person(const std::string &In, const char *fn = "Heyyou");
    ~Person();

    void Show() const;
    void FormalShow() const;
};

#endif
