#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <charconv>
#include <cassert>

void d2str2d(double value1)
{
    std::cout << "in:  " << value1 << '\n';

    // convert to character sequence:
    char str[1000];
    std::to_chars_result res1 = std::to_chars(str, str + 999, value1);
    *res1.ptr = '\0';  // add trailing null character

    std::cout << "str: " << str << '\n';
    assert(res1.ec == std::errc{});

    // read back from character sequence:
    double value2;
    std::from_chars_result res2 = std::from_chars(str, str + 999, value2);

    std::cout << "out: " << value2 << '\n';
    assert(res2.ec == std::errc{});

    assert(value1 == value2);  // should never fail
}


int main()
{
    std::vector<double> coll{0.1, 0.3, 0.00001};

    // create two slightly different floating-point values:
    auto sum1 = std::accumulate(coll.begin(), coll.end(),
                                0.0, std::plus<>());
    auto sum2 = std::accumulate(coll.rbegin(), coll.rend(),
                                0.0, std::plus<>());

    // look the same:
    std::cout << "sum1:  " << sum1 << '\n';
    std::cout << "sum1:  " << sum2 << '\n';

    // but are different:
    std::cout << std::boolalpha << std::setprecision(20);
    std::cout << "equal: " << (sum1 == sum2) << '\n'; // false !!
    std::cout << "sum1:  " << sum1 << '\n';
    std::cout << "sum1:  " << sum2 << '\n';
    std::cout << '\n';

    // check round-trip:
    d2str2d(sum1);
    d2str2d(sum2);
}
