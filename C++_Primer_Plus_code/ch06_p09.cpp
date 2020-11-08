#include <iostream>
#include <fstream>
#include <string>

struct ZVL
{
    std::string name;
    double donate;
};

int main()
{
    std::ifstream fileinp;
    fileinp.open("ch06_p09.txt");

    if (!fileinp.is_open())
    {
        std::cout << "Cound not open file." << std::endl;
        std::cout << "The program will be closed." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Number of Patrons: ";

    int mecenat_count;
    (fileinp >> mecenat_count).get();

    std::cout << mecenat_count << std::endl;
    ZVL *zvl = new ZVL[mecenat_count];

    for (int i = 0; i < mecenat_count; i++)
    {
        if ( ! std::getline(fileinp, zvl[i].name, '\n') )
        {
            break;
        }
        std::cout << "The name of the patron has been entered: ";
        std::cout << zvl[i].name << std::endl;
        (fileinp >> zvl[i].donate).get();
        std::cout << "Donation amount entered: ";
        std::cout << zvl[i].donate << std::endl;
        std::cout << std::endl;
    }

    int grand_patrons_count = 0;
    std::cout << "Grand Patrons: " << std::endl;

    for (int i = 0; i < mecenat_count; i++)
    {
        if (zvl[i].donate >= 10000)
        {
            std::cout << zvl[i].name << " = $" << zvl[i].donate << std::endl;
            grand_patrons_count++;
        }
    }

    if (grand_patrons_count == 0)
    {
        std::cout << "NONE!" << std::endl;
    }

    int patrons_count = 0;
    std::cout << "Patrons: " << std::endl;

    for (int i = 0; i < mecenat_count; i++)
    {
        if (zvl[i].donate < 10000)
        {
            std::cout << zvl[i].name << " = $" << zvl[i].donate << std::endl;
            patrons_count++;
        }
    }

    if (patrons_count == 0)
    {
        std::cout << "NONE!" << std::endl;
    }

    delete [] zvl;
    fileinp.close();

    return 0;
}
