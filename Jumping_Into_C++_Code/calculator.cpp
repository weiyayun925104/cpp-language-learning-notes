#include <cmath>
#include "calculator.h"

double add(double left, double right)
{
    return (left + right);
}

double subtract(double left, double right)
{
    return (left - right);
}

double multiply(double left, double right)
{
    return (left * right);
}

double divide(double left, double right)
{
    if (right == 0)
    {
        return INFINITY;
    }
    return (left / right);
}
