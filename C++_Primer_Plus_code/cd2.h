#pragma once
#ifndef CD2_H_
#define CD2_H_
#include <iostream>
#include <cstring>

class Cd
{
private:
    char *performers;
    char *label;
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
    char *cdname;
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
