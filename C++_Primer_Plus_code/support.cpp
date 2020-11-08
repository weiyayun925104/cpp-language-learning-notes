#include <iostream>

using std::cout;
extern double warming;

void update(double dt);
void local();

void update(double dt)
{
    extern double warming;
    warming += dt;
    cout << "Updating global warming to " << warming << " degrees.\n";
}

void local()
{
    double warming = 0.8;
    cout << "Local warming = " << warming << " degrees.\n";
    cout << "But global warming = " << ::warming << " degrees.\n";
}
