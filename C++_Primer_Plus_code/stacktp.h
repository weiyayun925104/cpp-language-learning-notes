#ifndef STACKTP_H_
#define STACKTP_H_

template <typename Type>
class Stack
{
private:
    enum { MAX = 10 };
    Type items[MAX];
    int top;
public:
    Stack();
    bool isempty();
    bool isfull();
    bool push(const Type &item);
    bool pop(Type &item);
};

template <typename Type>
Stack<Type>::Stack()
{
    top = 0;
}

template <typename Type>
bool Stack<Type>::isempty()
{
    return top == 0;
}

template <typename Type>
bool Stack<Type>::isfull()
{
    return top == MAX;
}

template <typename Type>
bool Stack<Type>::push(const Type &item)
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
    {
        return false;
    }
}

template <class Type>
bool Stack<Type>::pop(Type &item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
    {
        return false;
    }
}

#endif
