#include <iostream>
#include "coordin.h"

int main()
{
    rect rplace;
    polar pplace;
    std::cout << "Enter the x and y values: ";
    while ( (std::cin >> rplace.x) && (std::cin >> rplace.y) )
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        std::cout << "Enter the x and y values (q to quit) : ";
    }
    std::cout << "Done.\n";

    return 0;
}
