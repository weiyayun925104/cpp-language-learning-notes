#include <iostream>
#include <string>
#include "stack_class.h"

int main()
{
    Stack st;
    char ch;
    customer po;
    double subtotal = 0.0;

    std::cout << "Type A to add the client,\n";
    std::cout << "P to delete the client, and Q to exit.\n";

    while (std::cin >> ch && toupper(ch) != 'Q')
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }

        if (!isalpha(ch))
        {
            std::cout << "Please enter A, P, Q\n";
            continue;
        }

        switch (ch)
        {
        case 'A':
        case 'a':
            std::cout << "Enter customer name: ";
            std::cin.getline(po.fullname, 36);
            std::cout << "Enter customer payment: ";
            (std::cin >> po.payment).get();

            if (st.isfull())
            {
                std::cout << "Stack already full\n";
            }
            else
            {
                st.push(po);
            }
            break;
        case 'P':
        case 'p':
            if (st.isempty())
            {
                std::cout << "Stack already empty\n";
            }
            else
            {
                st.pop(po);
                subtotal += po.payment;
                std::cout << "Client " << po.fullname << " was deleted\n";
                std::cout << "Total customer payment : " << subtotal << '\n';
            }
            break;
        default :
            std::cout << "Please enter A, P, Q\n";
            continue;
            break;
        }
        std::cout << "Type A to add the client,\n";
        std::cout << "P to delete the client, and Q to exit.\n";
    }
    std::cout << "Done.\n";

    return 0;
}
