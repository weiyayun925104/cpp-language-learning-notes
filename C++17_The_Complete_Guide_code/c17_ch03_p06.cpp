#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <variant>

template<typename... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};

template<typename... Ts>
overload(Ts...) -> overload<Ts...>;

int main()
{
    using Var = std::variant<int, double, std::string>;

    std::vector<Var> values {42, 0.19, "hello world", 0.815};

    for (const Var &val : values)
    {
        std::visit([] (const auto & v)
        {
            if constexpr(std::is_same_v<decltype(v), const std::string &>)
            {
                std::cout << '"' << v << "\" ";
            }
            else
            {
                std::cout << v << ' ';
            }
        },
        val);
    }
}
