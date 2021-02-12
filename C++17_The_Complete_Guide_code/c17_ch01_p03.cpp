
#include <iostream>

struct Point
{
    double x, y;
};

Point midpoint(const Point& p1, const Point& p2)
{
    return { (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
}

int main()
{
    Point p1{ 1, 2 };
    Point p2{ 3, 4 };
    auto [x, y] = midpoint(p1, p2);
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}
