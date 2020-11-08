#pragma once
#ifndef GOLF_CLASS_H_
#define GOLF_CLASS_H_

class Golf
{
private:
    static const int Len = 128;
    char fullname[Len];
    int handicap;
public:
    Golf();
    Golf(const char *name, int hc);
    ~Golf();
    int set_golf();
    void show_golf();
};

#endif
