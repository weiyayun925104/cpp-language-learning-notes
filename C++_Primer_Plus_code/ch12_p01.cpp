#include <iostream>
#include "cow.h"

int main()
{
    {
        std::cout << "Cow 1:\n";
        Cow Cow1;

        std::cout << "Cow 2:\n";
        Cow Cow2("Cow2", "HOBBY", 89);

        std::cout << "Cow 3:\n";
        Cow Cow3 = Cow2;

        std::cout << "Cow 4:\n";
        Cow Cow4;
        Cow4 = Cow2;


        std::cout << std::endl;

        std::cout << "Cow 1:\n" << Cow1;
        std::cout << "Cow 2:\n" << Cow2;
        std::cout << "Cow 3:\n" << Cow3;
        std::cout << "Cow 4:\n" << Cow4;

        std::cout << std::endl;
    }

    return 0;
}
