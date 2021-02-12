#include <iostream>
#include <string>

template <typename T>
std::string asString(T x)
{
    if constexpr(std::is_same_v<T, std::string>)
    {
        return x;                  // statement invalid if no conversion to string
    }
    else if constexpr(std::is_arithmetic_v<T>)
    {
        return std::to_string(x);  // statement invalid if x is not numeric
    }
    else
    {
        return std::string(x);     // statement invalid if no conversion to string
    }
}

int main()
{
    std::cout << asString(42) << '\n';
    std::cout << asString(std::string("hello")) << '\n';
    std::cout << asString("hello") << '\n';
}
