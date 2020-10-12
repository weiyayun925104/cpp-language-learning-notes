#include <iostream>
#include <string>
#include "binarytree.h"

using namespace std;

int main()
{
    node *tree = nullptr;
    bool exitProgram = false;
    int choice = 0;
    int numberOfNodes = 0;

    while(!exitProgram)
    {
        choice = 0;
        if (tree == nullptr)
        {
            numberOfNodes = 0;
        }
        else
        {
            numberOfNodes = tree->count_of_nodes;
        }
        cout << "Please choose from the following options:\n";
        cout << "0. Exit\n";
        cout << "1. Add entry\n";
        if (numberOfNodes > 0)
        {
            cout << "2. Update entry\n";
            cout << "3. Delete entry\n";
            cout << "4. Display entry\n";
        }
        cin >> choice;
        cin.clear();
        cin.ignore(80, '\n');

        cout << '\n';

        switch (choice)
        {
        case 0:
            exitProgram = true;
            break;
        case 1:
            tree = add_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 2:
            tree = update_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 3:
            tree = delete_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 4:
            display_entry(tree);
            break;
        default:
            exitProgram = true;
            break;
        }
    }

    destroyTreePostOrder(tree);
}
