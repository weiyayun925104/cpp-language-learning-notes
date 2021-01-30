#include <iostream>
#include <locale>
 
int main()
{
    std::locale loc = std::locale("en_US.utf8"); // user's preferred locale
    std::cout << loc.name() << std::endl;
    std::cout << "Your currency string is "
              << std::use_facet<std::moneypunct<char, true>>(loc).curr_symbol() << '\n';
    std::cout << "std::use_facet<std::ctype<char>>(loc).toupper('a') = "
              << std::use_facet<std::ctype<char>>(loc).toupper('a') << '\n';
}
