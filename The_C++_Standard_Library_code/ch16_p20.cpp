// wbuffer_convert example
#include <iostream>       // std::cout, std::ios, std::wostream
#include <locale>         // std::wbuffer_convert
#include <codecvt>        // std::codecvt_utf8
#include <fstream>        // std::filebuf

int main ()
{
    using std::locale;
    using std::wistream;
    using std::wostream;
    using std::wofstream;
    using std::wifstream;
    using std::wbuffer_convert;
    using std::codecvt_utf8;

    auto loc_utf8=locale(locale("en_US.utf8"), new codecvt_utf8<wchar_t>);
    wofstream wfo("ch16_p20.txt");
    wfo.imbue(loc_utf8);

    wfo << L"Test\n";
    wfo.close();
    std::wcout << L"Test\n";

    return 0;
}
