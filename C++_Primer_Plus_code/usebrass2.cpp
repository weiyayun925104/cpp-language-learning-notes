#include <iostream>
#include "brass.h"

const int CLIENTS = 4;

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    Brass *p_clients[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;
    for (int i = 0; i < CLIENTS; i++)
    {
        cout << "Enter client's name: ";
        std::getline(cin, temp, '\n');
        cout << "Enter client's account number: ";
        cin >> tempnum;
        cout << "Enter opening balance: $";
        cin >> tempbal;
        while (cin.get() != '\n')
        {
            continue;
        }
        cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";
        while (cin >> kind && (kind != '1' && kind != '2'))
        {
            while (cin.get() != '\n')
            {
                continue;
            }
            cout << "Enter either 1 or 2 : ";
        }
        while (cin.get() != '\n')
        {
            continue;
        }
        if (kind == '1')
        {
            p_clients[i] = new Brass(temp, tempnum, tempbal);
        }
        else
        {
            double tmax, trate;
            cout << "Enter the overdraft limit: $";
            cin >> tmax;
            cout << "Enter the interest rate as a decimal fraction: ";
            cin >> trate;
            while (cin.get() != '\n')
            {
                continue;
            }
            p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
        }
    }
    cout << endl;
    for (int i = 0; i < CLIENTS; i++)
    {
        p_clients[i]->ViewAcct();
        cout << endl;
    }
    for (int i = 0; i < CLIENTS; i++)
    {
        delete p_clients[i];
    }
    cout << "Done.\n";

    return 0;
}
