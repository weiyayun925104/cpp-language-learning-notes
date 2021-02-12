#include <iostream>

struct BitField
{
    unsigned int f1 : 6;
    unsigned int f2 : 6;
    unsigned int f3 : 6;
};

int main()
{
    BitField b{ 1, 2, 3 };
    auto& [f1, f2, f3] = b;
    f2 = 4;
    auto print = [&b2 = b] { std::cout << b2.f1 << " " << b2.f2 << " " << b2.f3 << std::endl; };
    print();
    f2 = 21;
    print();
}
