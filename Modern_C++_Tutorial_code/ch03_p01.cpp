#include <iostream>
#include <memory>
#include <utility>

int main()
{
    auto important = std::make_unique<int>(1);
    auto  add  =  [v1  =  1,  v2  =  std::move(important)](int  x,  int  y)  ->  int
    {
        return x + y + v1 + (*v2);
    };
    std::cout  <<  add(3, 4)  <<  std::endl;
    return  0;
}
