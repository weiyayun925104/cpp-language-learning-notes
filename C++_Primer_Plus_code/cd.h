#pragma once
#ifndef CD_H_
#define CD_H_
#include <iostream>
#include <cstring>

class Cd
{
private:
    char performers[50];
    char label[20];
    int selections;
    double playtime;
public:
    Cd();
    Cd(const char *perf, const char *leb, int sel, double playt);
    Cd(const Cd &d);
    virtual ~Cd();
    virtual void Report() const;
    Cd &operator = (const Cd &d);
};

class Classic : public Cd
{
private:
    static const int lenght = 40;
    char cdname[lenght];
public:
    Classic();
    Classic(const char *name, Cd &cd);
    Classic(const char *name, const char *perf, const char *leb, int sel, double playt);
    Classic(const Classic &c);
    ~Classic();
    virtual void Report() const;
    Classic &operator = (const Classic &c);
};

#endif
