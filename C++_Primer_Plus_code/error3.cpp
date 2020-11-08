#include <iostream>
#include <cfloat>

double hmean(double a, double b);

int main()
{
    double x, y, z;

    std::cout << "Enter two numbers <q to quit>: ";
    while (std::cin >> x && std::cin >> y)
    {
        try
        {
            z = hmean(x, y);
        }
        catch (const char *s)
        {
            std::cout << s << std::endl;
            std::cout << "Enter two numbers <q to quit>: ";
            continue;
        }
        std::cout << "Harmonic mean of " << x << " and " << y
                  << " is " << z << std::endl;
        std::cout << "Enter two numbers <q to quit>: ";
    }
    std::cout << "Done.\n";

    return 0;
}

double hmean(double a, double b)
{
    if (a == -b)
    {
        throw "bad hmean() arguments: a = -b not allowed";
    }
    return (2.0 * a * b) / (a + b);
}
