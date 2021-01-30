#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

int main()
{
    using std::locale;
    using std::wistream;
    using std::wostream;
    using std::wofstream;
    using std::wifstream;
    using std::wbuffer_convert;
    using std::codecvt_utf8;

    std::stringbuf utf8buf(u8"z\u00df\u6c34\U0001f34c");
    std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv_in(&utf8buf);
    std::wistream ucsbuf(&conv_in);
    std::cout << "Reading from a UTF-8 stringbuf via wbuffer_convert:\n";
    for(wchar_t c; ucsbuf.get(c); )
        std::cout << std::hex << std::showbase << c << '\n';

    auto loc_utf8=locale(locale("en_US.utf8"), new codecvt_utf8<wchar_t>);
    wofstream wfo("ch16_p21.txt");
    wfo.imbue(loc_utf8);

    wfo << L"z\u00df\u6c34\U0001f34c\n";
    wfo.close();
}
