
#include <iostream>
#include <map>

int main()
{
    std::map<int, int> map;
    auto&& [iter, inserted] = map.insert({1, 2});
    if (inserted)
        std::cout << "inserted successfully" << std::endl;
    for (auto&& [key, value] : map)
        std::cout << "[" << key << ", " << value << "]" << std::endl;
}
