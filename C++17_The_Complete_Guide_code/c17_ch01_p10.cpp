#include <iostream>
#include <string>
#include <utility>

class Customer
{
private:
    std::string first;
    std::string last;
    long val;
public:
    Customer (std::string f, std::string l, long v)
        : first{std::move(f)}, last{std::move(l)}, val{v}
    {
    }
    const std::string &firstname() const
    {
        return first;
    }
    std::string &firstname()
    {
        return first;
    }
    const std::string &lastname() const
    {
        return last;
    }
    std::string &lastname()
    {
        return last;
    }
    long value() const
    {
        return val;
    }
    long &value()
    {
        return val;
    }
};

template<>
struct std::tuple_size<Customer>
{
    static constexpr int value = 3;   // we have 3 attributes
};

template<>
struct std::tuple_element<2, Customer>
{
    using type = long;                // last attribute is a long
};

template<std::size_t Idx>
struct std::tuple_element<Idx, Customer>
{
    using type = std::string;         // the other attributes are strings
};


// define specific getters:
template<std::size_t I> decltype(auto) get(Customer &c)
{
    static_assert(I < 3);
    if constexpr (I == 0)
    {
        return c.firstname();
    }
    else if constexpr (I == 1)
    {
        return c.lastname();
    }
    else    // I == 2
    {
        return c.value();
    }
}
template<std::size_t I> decltype(auto) get(const Customer &c)
{
    static_assert(I < 3);
    if constexpr (I == 0)
    {
        return c.firstname();
    }
    else if constexpr (I == 1)
    {
        return c.lastname();
    }
    else    // I == 2
    {
        return c.value();
    }
}
template<std::size_t I> decltype(auto) get(Customer &&c)
{
    static_assert(I < 3);
    if constexpr (I == 0)
    {
        return std::move(c.firstname());
    }
    else if constexpr (I == 1)
    {
        return std::move(c.lastname());
    }
    else    // I == 2
    {
        return c.value();
    }
}

int main()
{
  Customer c{"Tim", "Starr", 42};
  auto [f, l, v] = c;
  std::cout << "f/l/v:    " << f << ' ' << l << ' ' << v << '\n';

  // modify structured bindings via references:
  auto&& [f2, l2, v2] = c;
  std::string s{std::move(f2)};
  f2 = "Ringo";
  v2 += 10;
  std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << '\n';
  std::cout << "c:        " << c.firstname() << ' '
            << c.lastname() << ' ' << c.value() << '\n';
  std::cout << "s:        " << s << '\n';
}
