#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include "vect.h"


int main()
{
    using VECTOR::Vector;

    std::srand(std::time(nullptr));

    std::vector<unsigned long> stepsResult;
    std::cout << "Enter number of attempts: ";
    int attempt = 0;
    std::cin >> attempt;
    while (std::cin.get() != '\n')
    {
        continue;
    }

    std::ofstream fout;
    fout.open("ch11_p03.txt");

    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;

    std::cout << "Enter target distance (q to quit) : ";
    target = 0.0;
    while (attempt > 0 && std::cin >> target)
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

        }
        stepsResult.push_back(steps);

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
        --attempt;
        if (attempt > 0)
        {
            std::cout << "Enter target distance (q to quit) : ";
            target = 0.0;
        }
    }
    std::cout << "The smallest number of steps is ";
    std::cout << *std::min_element(stepsResult.begin(), stepsResult.end());
    std::cout << '\n';

    std::cout << "The largest number of steps is ";
    std::cout << *std::max_element(stepsResult.begin(), stepsResult.end());
    std::cout << '\n';

    std::cout << "The average number of steps is ";
    std::cout << std::accumulate(stepsResult.begin(), stepsResult.end(), 0) / stepsResult.size();
    std::cout << '\n';

    fout.close();
    std::cout << "Done.\n";
    if (attempt > 0)
    {
        std::cin.clear();
        while (std::cin.get() != '\n')
        {
            continue;
        }
    }

    return 0;
}
