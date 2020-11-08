#include <iostream>
#include "emp.h"

int main()
{
    employee em("Trip", "Harris", "Thumper");
    std::cout << em << std::endl;
    em.ShowAll();

    std::cout << std::endl;

    manager ma("Amorphia", "Spindragon", "Nuancer", 5);
    std::cout << ma << std::endl;
    ma.ShowAll();

    std::cout << std::endl;

    fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
    std::cout << fi << std::endl;
    fi.ShowAll();

    std::cout << std::endl;

    highfink hf(ma, "Curly Kew");
    hf.ShowAll();

    std::cout << std::endl;

    highfink hf2;
    hf2.SetAll();
    hf2.ShowAll();

    std::cout << std::endl;

    std::cout << "Using an abstr_emp * pointer:\n";

    abstr_emp *tri[4] = { &em, &fi, &hf, &hf2 };
    for (int i = 0; i < 4; i++)
    {
        tri[i]->ShowAll();
        std::cout << std::endl;
    }

    return 0;
}
