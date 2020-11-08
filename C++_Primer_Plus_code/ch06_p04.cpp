#include <iostream>

const int strsize = 128;

struct bop
{
    char fullname[strsize];
    char title[strsize];
    char bopname[strsize];
    int preference;
};

int main()
{
    std::cout << "Benevolent Order of Programmers Report" << std::endl;
    std::cout << "a. display by name" << std::endl;
    std::cout << "b. display by title" << std::endl;
    std::cout << "c. display by bopname" << std::endl;
    std::cout << "d. display by preference" << std::endl;
    std::cout << "q. quit" << std::endl;
    std::cout << "Enter a,b,c,d or q: ";

    bop organization[4] =
    {
        { "Wimp Macho", "Wimp Macho - WM", "WM", 0 },
        { "Raki Rhodes", "Raki Rhodes - RR", "RR", 1 },
        { "Celia Laiter", "Celia Laiter - CL", "CL", 2 },
        { "Hoppy Hipman", "Hoppy Hipman - HH", "HH", 0 }
    };

    char enter;
    while ( std::cin.get(enter) )
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        switch (enter)
        {
        case 'a':
        case 'A':
            for (int i = 0; i < 4; i++)
            {
                std::cout << organization[i].fullname << std::endl;
            }
            std::cout << "Enter a,b,c,d or q: ";
            break;
        case 'b':
        case 'B':
            for (int i = 0; i < 4; i++)
            {
                std::cout << organization[i].title << std::endl;
            }
            std::cout << "Enter a,b,c,d or q: ";
            break;
        case 'c':
        case 'C':
            for (int i = 0; i < 4; i++)
            {
                std::cout << organization[i].bopname << std::endl;
            }
            std::cout << "Enter a,b,c,d or q: ";
            break;
        case 'd':
        case 'D':
            for (int i = 0; i < 4; i++)
            {
                switch (organization[i].preference)
                {
                case 0:
                    std::cout << organization[i].fullname << std::endl;
                    break;
                case 1:
                    std::cout << organization[i].title << std::endl;
                    break;
                case 2:
                    std::cout << organization[i].bopname << std::endl;
                    break;
                default:
                    std::cout << organization[i].fullname << std::endl;
                    break;
                }
            }
            std::cout << "Enter a,b,c,d or q: ";
            break;
        case 'q':
        case 'Q':
            std::cout << "Done." << std::endl;

            return 0;
            break;
        default:
            std::cout << "Enter a,b,c,d or q: ";
            break;
        }
    }
    return 0;
}
