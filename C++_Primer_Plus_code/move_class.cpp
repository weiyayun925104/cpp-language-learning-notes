#include <iostream>
#include "move_class.h"

Move::Move(double a, double b)
{
    x = a;
    y = b;
}
void Move::show_move() const
{
    std::cout << "X = " << x << std::endl;
    std::cout << "Y = " << y << std::endl;
}

Move Move::add(const Move &m) const
{
    x += m.x;
    y += m.y;
    return *this;
}

void Move::reset(double a, double b)
{
    x = a;
    y = b;
}
