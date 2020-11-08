#include <iostream>
#include <string>
#include <cctype>
#include "stacktp.h"

using std::cin;
using std::cout;


int main()
{
    Stack<std::string> st;
    char ch;
    std::string po;
    cout << "Please enter A to add a purchase order,\n"
         << "P to process a PO, or Q to quit.\n";
    while (cin >> ch && std::toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')
        {
            continue;
        }
        if (!std::isalpha(ch))
        {
            cout << "Please enter A, P, Q\n";
            continue;
        }
        switch (ch)
        {
        case 'A':
        case 'a':
            cout << "Enter a PO number to add: ";
            std::getline(cin, po, '\n');
            if (st.isfull())
            {
                cout << "stack already full\n";
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
                cout << "stack already empty\n";
            }
            else
            {
                st.pop(po);
                cout << "PO #" << po << " popped\n";
            }
            break;
        default :
            std::cout << "Please enter A, P, Q\n";
            continue;
            break;
        }
        cout << "Please enter A to add a purchase order,\n"
             << "P to process a PO, or Q to quit.\n";
    }
    cout << "Done.\n";

    return 0;
}
