#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "emp2.h"

const int MAX = 10;

void displayMenu(void);
void eatline(void);

int main()
{
    abstr_emp *pc[MAX];
    std::cout << "You may enter of to " << MAX << " employees" << std::endl;

    int count = 0;
    char ch;
    std::ifstream fin;
    fin.open("employeeList.dat");

    if (fin.is_open())
    {
        int classtype = 0;
        while ( fin >> classtype && fin.get(ch) )
        {
            switch (classtype)
            {
            case abstr_emp::Employee:
                std::cout << "Creating an employee object" << std::endl;
                pc[count] = new employee;
                pc[count++]->getall(fin);
                break;
            case abstr_emp::Manager:
                std::cout << "Creating an manager object" << std::endl;
                pc[count] = new manager;
                pc[count++]->getall(fin);
                break;
            case abstr_emp::Fink:
                std::cout << "Creating an fink object" << std::endl;
                pc[count] = new fink;
                pc[count++]->getall(fin);
                break;
            case abstr_emp::Highfink:
                std::cout << "Creating an highfink object" << std::endl;
                pc[count] = new highfink;
                pc[count++]->getall(fin);
                break;
            default:
                std::cerr << "It looks like an error has occurred" << std::endl;
                break;
            }
        }
        std::cout << "Here is your current employee list: " << std::endl;
        for (int i = 0; i < count; i++)
        {
            pc[i]->ShowAll();
            std::cout << std::endl;
        }
        fin.close();
    }

    while (count < MAX)
    {
        displayMenu();
        std::cin >> ch;
        eatline();

        switch (ch)
        {
        case 'a':
            pc[count] = new employee;
            pc[count]->SetAll();
            count++;
            break;
        case 'b':
            pc[count] = new manager;
            pc[count]->SetAll();
            count++;
            break;
        case 'c':
            pc[count] = new fink;
            pc[count]->SetAll();
            count++;
            break;
        case 'd':
            pc[count] = new highfink;
            pc[count]->SetAll();
            count++;
            break;
        case 'q':
            break;
        default:
            std::cout << "Error input not recognized" << std::endl;
            continue;
            break;
        }
        if (ch == 'q')
        {
            break;
        }
    }

    std::ofstream fout;
    fout.open("employeeList.dat");

    if (!fout.is_open())
    {
        std::cerr << "Error, cannot open employeeList.dat" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Here's our updated list: " << std::endl;

    for (int i = 0; i < count; i++)
    {
        pc[i]->ShowAll();
        std::cout << std::endl;
        pc[i]->writeall(fout);
    }
    fout.close();
    for (int i = 0; i < count; i++)
    {
        delete pc[i];
    }

    return 0;
}

void displayMenu(void)
{
    std::cout << "Select one of the following:" << std::endl;
    std::cout << std::left;
    std::cout << std::setw(20) << "a. Employee";
    std::cout << std::setw(20) << "b. Manager";
    std::cout << std::endl;
    std::cout << std::setw(20) << "c. Fink";
    std::cout << std::setw(20) << "d. Highfink";
    std::cout << std::endl;
    std::cout << "(q to quit)" << std::endl;
}

void eatline(void)
{
    while (std::cin.get() != '\n')
    {
        continue;
    }
}
