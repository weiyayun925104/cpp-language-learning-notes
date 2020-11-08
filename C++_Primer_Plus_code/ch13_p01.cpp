#include <iostream>
#include "cd.h"

void Bravo(const Cd &disk);

int main()
{
    Cd c1("Beatles", "Capitol", 14, 35.5);
    Classic c2 = Classic("Piano sonata in b flat, Fantasia in C", "Alfred Brendel", "Phillips", 2, 57.17);
    Cd *pcd = &c1;

    std::cout << "Using object directly: " << std::endl;
    std::cout << std::endl;
    c1.Report();
    std::cout << std::endl;
    c2.Report();
    std::cout << std::endl;

    std::cout << "Using type cd* pointer to objects: " << std::endl;;
    std::cout << std::endl;
    pcd->Report();
    std::cout << std::endl;
    pcd = &c2;
    pcd->Report();
    std::cout << std::endl;

    std::cout << "Calling a function with a Cd reference argument: " << std::endl;;
    std::cout << std::endl;
    Bravo(c1);
    std::cout << std::endl;
    Bravo(c2);
    std::cout << std::endl;

    std::cout << "Testing assignment: " << std::endl;
    Classic copy;
    copy = c2;
    copy.Report();

    return 0;
}

void Bravo(const Cd &disk)
{
    disk.Report();
}
