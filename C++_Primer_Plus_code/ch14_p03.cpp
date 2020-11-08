#include <iostream>
#include <cstring>
#include "workermi.h"
#include "queuetp.h"

const int SIZE = 5;

int main()
{
    QueueTp<Worker *> q;
    Worker *pw;
    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        std::cout << "Enter the employee category:\n";
        std::cout << "w: waiter  s: singer  ";
        std::cout << "t: singing waiter  q: quit\n";

        char choice = 0;
        std::cin >> choice;
        while (std::cin.get() != '\n')
        {
            continue;
        }
        while (std::strchr("wstq", choice) == nullptr)
        {
            std::cout << "Please enter a w, s, t, or q: ";
            std::cin >> choice;
            while (std::cin.get() != '\n')
            {
                continue;
            }
        }

        if (choice == 'q')
        {
            break;
        }

        switch (choice)
        {
        case 'w':
            pw = new Waiter;
            break;
        case 's':
            pw = new Singer;
            break;
        case 't':
            pw = new SingingWaiter;
            break;
        default:
            pw = new SingingWaiter;
            break;
        }

        pw->Set();
        q.enqueue(pw);
    }

    std::cout << "\nHere is your staff:\n";

    for (int i = 0; i < ct; i++)
    {
        q.dequeue(pw);
        pw->Show();
        delete pw;
        std::cout << std::endl;
    }
    std::cout << "Done.\n";

    return 0;
}
