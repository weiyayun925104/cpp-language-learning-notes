#include <iostream>
#include <array>
#include <numeric>
#include <iterator>

int main()
{
    std::array coll{3, 1, 7, 0, 4, 1, 6, 3};

    std::cout << " inclusive_scan():    ";
    std::inclusive_scan(coll.begin(), coll.end(),
                        std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n exclusive_scan():  ";
    std::exclusive_scan(coll.begin(), coll.end(),
                        std::ostream_iterator<int>(std::cout, " "),
                        0);  // mandatory

    std::cout << "\n exclusive_scan():  ";
    std::exclusive_scan(coll.begin(), coll.end(),
                        std::ostream_iterator<int>(std::cout, " "),
                        100);  // mandatory

    std::cout << "\n inclusive_scan():      ";
    std::inclusive_scan(coll.begin(), coll.end(),
                        std::ostream_iterator<int>(std::cout, " "),
                        std::plus{}, 100);

    std::cout << "\n exclusive_scan():  ";
    std::exclusive_scan(coll.begin(), coll.end(),
                        std::ostream_iterator<int>(std::cout, " "),
                        100, std::plus{});  // note: different order
}

