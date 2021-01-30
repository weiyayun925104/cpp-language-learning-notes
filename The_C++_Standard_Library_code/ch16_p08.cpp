#include <iostream>     // std::cin, std::cout
#include <iomanip>      // std::get_money
#include <locale>

int main ()
{
    using std::get_money;
    using std::put_money;
    using std::locale;

    locale locG("en_US.utf8");

    // use German locale and ensure that the currency is written:
    std::cin.imbue(locG);
    std::cout.imbue(locG);
    std::cout << std::showbase;

    long double price;
    std::cout << "Please, enter the price: ";
    std::cin >> std::get_money(price);
    if (std::cin.fail())
    {
        std::cout << "Error reading price\n";
    }
    else
    {
        std::cout << price << std::endl;
        std::cout << "The price entered is: " << std::put_money(price, false) << ", " << std::put_money(price, true) << '\n';
    }

    return 0;
}
