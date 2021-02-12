#include <iostream>
#include <utility>
#include <tuple>

int main()
{
    using std::cout;
    using std::endl;

    std::pair pair{ 1, 2.0 };
    int number = 3;
    std::tuple<int&> tuple(number);
    const auto& [i, f] = pair;
    cout << i << ", " << f << endl;
    const auto& [ri] = tuple;
    cout << ri << endl;
}
