#include <iostream>
#include "bank_account.h"

void print_menu();
void transactions_menu();

int main()
{
    Bank_account Acc;
    Acc.show_account();
    std::string name_depositor;
    std::string account_number;
    double balance = 0;
    int menu = 0;

    print_menu();
    while (std::cin >> menu && menu != 3)
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        switch (menu)
        {
        case 1:
            std::cout << "Enter the name of the account holder: " << std::endl;
            std::getline(std::cin, name_depositor, '\n');

            std::cout << "Enter the account number: " << std::endl;
            std::getline(std::cin, account_number, '\n');

            std::cout << "Enter the current balance: " << std::endl;
            std::cin >> balance;
            while (std::cin.get() != '\n')
            {
                continue;
            }

            Acc = Bank_account(name_depositor, account_number, balance);
            menu = 0;
            print_menu();
            break;
        case 2:
            menu = 0;
            transactions_menu();
            while (std::cin >> menu && menu != 4)
            {
                while (std::cin.get() != '\n')
                {
                    continue;
                }

                switch (menu)
                {
                case 1:
                    std::cout << "Enter the amount to be added to the balance: ";
                    std::cin >> balance;
                    while (std::cin.get() != '\n')
                    {
                        continue;
                    }
                    Acc.add_balance(balance);
                    menu = 0;
                    transactions_menu();
                    break;
                case 2:
                    std::cout << "Enter the amount to be withdrawn from the balance: ";
                    std::cin >> balance;
                    while (std::cin.get() != '\n')
                    {
                        continue;
                    }
                    Acc.cash_withdrawal(balance);
                    menu = 0;
                    transactions_menu();
                    break;
                case 3:
                    Acc.show_account();
                    menu = 0;
                    transactions_menu();
                    break;
                default:
                    std::cout << "Please Enter 1 or 2 or 3 or 4\n";
                    menu = 0;
                    transactions_menu();
                    break;
                }
            }
            menu = 0;
            print_menu();
            break;
        default:
            std::cout << "Please Enter 1 or 2 or 3\n";
            menu = 0;
            print_menu();
            break;
        }
    }

    std::cout << "Done.\n";

    return 0;
}

void print_menu()
{
    std::cout << "[1] - Create an account" << std::endl;
    std::cout << "[2] - Account Operations" << std::endl;
    std::cout << "[3] - Quit" << std::endl;
}

void transactions_menu()
{
    std::cout << "[1] - Add cash" << std::endl;
    std::cout << "[2] - Withdraw cash" << std::endl;
    std::cout << "[3] - Display Information" << std::endl;
    std::cout << "[4] - Quit" << std::endl;
}
