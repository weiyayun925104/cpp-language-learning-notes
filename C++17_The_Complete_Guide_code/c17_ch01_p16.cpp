#include <iostream>
#include <initializer_list>
#include <iomanip>

int main()
{
    // init list of floating-point values:
    std::initializer_list<double> values
    {
        0x1p+4,        // 16
        0x1.4p+3,          // 10
        0x1.4p+5,        // 40
        5e0,          // 5
        0x1.4p+2,   // 5
        1e5,          // 100000
        0x1.86ap+16, // 100000
        0x1.8dp+5,  // 49.625
    };

    // print all values both as decimal and hexadecimal value:
    for (double d : values)
    {
        std::cout << "dec: " << std::setw(6) << std::defaultfloat << d
                  << "  hex: " << std::hexfloat << d << '\n';
    }
}

