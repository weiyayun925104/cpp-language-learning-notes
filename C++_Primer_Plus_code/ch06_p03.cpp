#include <iostream>

int main()
{
    std::cout << "Please enter one of the following choices: " << std::endl;
    std::cout << "c) carnivore p) pianist" << std::endl << "t) tree g) game" << std::endl;
    char enter;

    while ( std::cin.get(enter) )
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        switch (enter)
        {
        case 'c':
        case 'C':
            std::cout << "Your choice is carnivore" << std::endl;
            break;
        case 'p':
        case 'P':
            std::cout << "Your choice is pianist" << std::endl;
            break;
        case 't':
        case 'T':
            std::cout << "Your choice is tree" << std::endl;
            break;
        case 'g':
        case 'G':
            std::cout << "Your choice is game" << std::endl;
            break;
        default:
            std::cout << "Please enter a c, p, t, or g: ";
            break;
        }
    }

    return 0;
}
