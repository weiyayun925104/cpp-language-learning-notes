#include <iostream>
#include "namesp.h"

namespace pers
{
    using std::cout;
    using std::cin;
    void getPerson(Person &rp)
    {
        cout << "Enter first name: ";
        std::getline(cin, rp.fname, '\n');
        cout << "Enter last name: ";
        std::getline(cin, rp.lname, '\n');
    }
    void showPerson(const Person &rp)
    {
        std::cout << rp.lname << ", " << rp.fname;
    }
}

namespace debts
{
    void getDebt(Debt &rd)
    {
        getPerson(rd.name);
        std::cout << "Enter debt: ";
        std::cin >> rd.amount;
        while (std::cin.get() != '\n')
        {
            continue;
        }
    }
    void showDebt(const Debt &rd)
    {
        showPerson(rd.name);
        std::cout << ": $" << rd.amount << std::endl;
    }
    double sumDebts(const Debt ar[], int n)
    {
        double total = 0;
        for (int i = 0; i < n; i++)
        {
            total += ar[i].amount;
        }
        return total;
    }
}
