#include <iostream>

void function1();
void function2();

int main()
{

    function1();
    function1();
    function2();
    function2();

    return 0;
}

void function1()
{
    std::cout << "Three blind mice" << std::endl;
}

void function2()
{
    std::cout << "See how they run" << std::endl;
}
