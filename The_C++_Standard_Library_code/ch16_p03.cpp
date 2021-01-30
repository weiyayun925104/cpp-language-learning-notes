#include <iostream>
#include <locale>

int main()
{
    const double number = 1000.25;
    std::wcout << L"default locale: " << number << L'\n';
    std::wcout.imbue(std::locale(std::wcout.getloc(),
                                 new std::numpunct_byname<wchar_t>("ru_RU.utf8")));
    std::wcout << L"default locale with russian numpunct: " << number << L'\n';
}
