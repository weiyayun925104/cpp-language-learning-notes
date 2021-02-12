#include <iostream>
#include <map>
#include <string>

template<typename T1, typename T2>
void print(const T1 &coll1, const T2 &coll2)
{
    std::cout << "values:\n";
    for (const auto& [key, value] : coll1)
    {
        std::cout << "  [" << key << ":" << value << "]";
    }
    std::cout << '\n';
    for (const auto& [key, value] : coll2)
    {
        std::cout << "  [" << key << ":" << value << "]";
    }
    std::cout << '\n';
}

int main()
{
    std::multimap<double, std::string> src {{1.1, "one"},
        {2.2, "two"},
        {3.3, "three"}};
    std::map<double, std::string> dst {{3.3, "old data"}};

    print(src, dst);

    // move some elements from multimap src to map dst:
    dst.insert(src.extract(src.find(1.1)));  // splice using an iterator
    dst.insert(src.extract(2.2));            // splice using the key

    print(src, dst);
}

