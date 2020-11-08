#pragma once
#ifndef STACK_CLASS_H_
#define STACK_CLASS_H_


struct customer
{
    char fullname[36];
    double payment;
};

typedef customer Item;

class Stack
{
private:
    enum { MAX = 10 };
    Item items[MAX];
    int top;
public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const Item &item);
    bool pop(Item &item);
};

#endif
