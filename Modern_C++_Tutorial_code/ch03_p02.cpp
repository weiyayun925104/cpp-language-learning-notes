#include <iostream>
class A
{
public:
    int *pointer;
    A(): pointer(new int(1))
    {
        std::cout << "construct " << pointer << std::endl;
    }
    A(A &a): pointer(new int(*a.pointer))
    {
        std::cout << "copy " << pointer << std::endl;
    }
    A(A &&a): pointer(a.pointer)
    {
        a.pointer = nullptr;
        std::cout << "move " << pointer << std::endl;
    }
    ~A()
    {
        std::cout << "destruct " << pointer << std::endl;
        delete pointer;
    }
};
A return_rvalue(bool test)
{

    A a, b;
    if(test) return a; // 等 价 于 static_cast<A&&>(a);
    else return b;	// 等价于 static_cast<A&&>(b);
}
int main()
{
    A  obj  =   return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return  0;
}
