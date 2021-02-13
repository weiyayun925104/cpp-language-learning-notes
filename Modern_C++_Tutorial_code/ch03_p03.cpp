#include <iostream>
#include <utility>

void reference(int &v)
{
    std::cout << "left reference" << std::endl;
}

void reference(int &&v)
{
    std::cout << "right reference" << std::endl;
}

template <typename T>
void pass(T &&v)
{
    std::cout << "normal pass: ";
    reference(v);
    std::cout << "std::move pass: ";
    reference(std::move(v));
    std::cout << "std::forward pass: ";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> pass: ";
    reference(static_cast < T && > (v));
}
int main()
{
    std::cout << "pass right val (1):" << std::endl;
    pass(1);

    std::cout << "pass left val (v):" << std::endl;
    int  v  =  1;
    pass(v);

    return  0;
}
