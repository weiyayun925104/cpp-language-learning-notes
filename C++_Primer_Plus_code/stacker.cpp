#include <iostream>
#include <cctype>
#include "stack.h"

int main()
{
    using namespace std;
    Stack st;
    char ch;
    unsigned long po;
    cout << "Please enter A to add a purchase order,\n"
         << "P to process a purchase order, or Q to quit.\n";
    while (cin >> ch && toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')
        {
            continue;
        }
        if (!isalpha(ch))
        {
            cout << "Please enter A, P, Q\n";
            continue;
        }
        switch (ch)
        {
        case 'A':
        case 'a':
            cout << "Enter a purchase order number to add: ";
            cin >> po;
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
                cout << "purchase order #" << po << " popped\n";
            }
            break;
        default :
            cout << "Please enter A, P, Q\n";
            continue;
            break;
        }
        cout << "Please enter A to add a purchase order,\n"
             << "P to process a purchase order, or Q to quit.\n";
    }
    cout << "Done.\n";

    return 0;
}
