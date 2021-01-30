#include <iostream>
#include <iomanip>
#include <locale>

struct my_punct : std::moneypunct_byname<char, false>
{
    my_punct(const char *name) : moneypunct_byname(name) {}
    string_type do_negative_sign() const
    {
        return "()";
    }
};

int main()
{
    std::locale loc("en_US.utf8");
    std::cout.imbue(loc);
    long double units = -123.45;
    std::cout << "In en_US.utf8 locale, " << units << " prints as "
              << std::showbase;
    // note, the following is equivalent to simply std::put_money(units)
    std::use_facet<std::money_put<char>>(loc).put(
    {std::cout}, false, std::cout, std::cout.fill(), units);
    std::cout << '\n';

    std::cout.imbue(std::locale(std::cout.getloc(), new my_punct("en_US.utf8")));
    std::cout << "With negative_sign set to \"()\", it prints  as ";
    std::use_facet<std::money_put<char>>(loc).put(
    {std::cout}, false, std::cout, std::cout.fill(), units);
    std::cout << '\n';
    std::cout << "With negative_sign set to \"()\", it prints  as ";
    std::use_facet<std::money_put<char>>(loc).put(
    {std::cout}, true, std::cout, std::cout.fill(), units);
    std::cout << '\n';
}
