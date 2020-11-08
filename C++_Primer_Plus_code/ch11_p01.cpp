#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "vect.h"


int main()
{
    using VECTOR::Vector;

    std::srand(std::time(nullptr));

    std::ofstream fout;
    fout.open("Vector.txt");

    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;

    std::cout << "Enter target distance (q to quit) : ";
    target = 0.0;
    while (std::cin >> target)
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        std::cout << "Enter step length: ";
        dstep = 0.0;
        if (!(std::cin >> dstep))
        {
            break;
        }
        while (std::cin.get() != '\n')
        {
            continue;
        }
        fout << "Target distance : ";
        fout << target << ",";
        fout << " Step length: ";
        fout << dstep << std::endl;

        while (result.magval() < target)
        {
            direction = std::rand() % 360;
            step.reset(dstep, direction, Vector::POL);
            result = result + step;
            steps++;

            fout << steps << ": " << result << std::endl;
            std::cout << steps << ": " << result << std::endl;
        }

        fout << "After " << steps << " steps, the subject has the following location:\n";
        std::cout << "After " << steps << " steps, the subject has the following location:\n";

        fout << result << std::endl;
        std::cout << result << std::endl;
        result.polar_mode();

        fout << " or\n" << result << std::endl;
        std::cout << " or\n" << result << std::endl;

        fout << "Average outward distance per step = ";
        std::cout << "Average outward distance per step = ";
        fout << result.magval() / steps << std::endl;
        std::cout << result.magval() / steps << std::endl;

        steps = 0;
        result.reset(0.0, 0.0);
        std::cout << "Enter target distance (q to quit) : ";
        target = 0.0;
    }
    fout.close();
    std::cout << "Done.\n";
    std::cin.clear();
    while (std::cin.get() != '\n')
    {
        continue;
    }

    return 0;
}
