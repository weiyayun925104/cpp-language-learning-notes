#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <iterator>

int main()
{
    std::string str = "$1.11 $2.22 $3.33";
    std::cout << std::fixed << std::setprecision(2);
 
    std::cout << '"' << str << "\" parsed with the I/O manipulator: ";
    std::istringstream s1(str);
    s1.imbue(std::locale("en_US.utf8"));
    long double val;
    while(s1 >> std::get_money(val))
        std::cout << val/100 << ' ';
    std::cout << '\n';
 
    str = "USD  1,234.56";
    std::cout << '"' << str << "\" parsed with the facet directly: ";
    std::istringstream s2(str);
    s2.imbue(std::locale("en_US.utf8"));
    auto& f = std::use_facet<std::money_get<char>>(s2.getloc());
    std::ios_base::iostate err;
    std::istreambuf_iterator<char> beg(s2), end;
    f.get(beg, end, true, s2, err, val);
    std::cout << val/100 << '\n';
}
