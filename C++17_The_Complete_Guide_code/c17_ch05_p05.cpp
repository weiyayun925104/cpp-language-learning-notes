#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<long, std::string> coll;

    for (int i = 0; i < 10; ++i)
    {
        std::string s{"Customer" + std::to_string(i)};
        coll.emplace(i, s);
    }

    // print element distances:
    for (const auto &elem : coll)
    {
        static long long lastVal = 0;
        long long val = reinterpret_cast<long long>(&elem);
        std::cout << "diff: " << (val - lastVal) << '\n';
        lastVal = val;
    }
}

