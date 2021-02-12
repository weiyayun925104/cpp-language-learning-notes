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
    std::string getFirst() const
    {
        return first;
    }
    std::string getLast() const
    {
        return last;
    }
    long getValue() const
    {
        return val;
    }
};

template<>
struct std::tuple_size<Customer> {
  static constexpr int value = 3;   // we have 3 attributes
};

template<>
struct std::tuple_element<2, Customer> {
  using type = long;                // last attribute is a long
};
template<std::size_t Idx>
struct std::tuple_element<Idx, Customer> {
  using type = std::string;         // the other attributes are strings
};

template<std::size_t> auto get(const Customer& c);
template<> auto get<0>(const Customer& c) { return c.getFirst(); }
template<> auto get<1>(const Customer& c) { return c.getLast(); }
template<> auto get<2>(const Customer& c) { return c.getValue(); }

int main()
{
  Customer c{"Tim", "Starr", 42};

  auto [f, l, v] = c;

  std::cout << "f/l/v:    " << f << ' ' << l << ' ' << v << '\n';

  // modify structured bindings:
  std::string s{std::move(f)};
  f = "Peter";
  l = "Waters";
  v += 10;
  std::cout << "f/l/v:    " << f << ' ' << l << ' ' << v << '\n';
  std::cout << "c:        " << c.getFirst() << ' '
            << c.getLast() << ' ' << c.getValue() << '\n';
  std::cout << "s:        " << s << '\n';
}
