#include <iostream>
#include <locale>
 
struct french_bool : std::numpunct<char> {
    string_type do_truename() const { return "vrai"; }
    string_type do_falsename() const { return "faux"; }
};
 
int main()
{
    std::cout << "default locale: "
              << std::boolalpha << true << ", " << false << '\n';
    std::cout.imbue(std::locale(std::cout.getloc(), new french_bool));
    std::cout << "locale with modified numpunct: "
              << std::boolalpha << true << ", " << false << '\n';
}
