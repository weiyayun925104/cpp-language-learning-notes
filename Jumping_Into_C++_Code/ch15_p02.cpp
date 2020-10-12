#include <iostream>

using namespace std;

struct Item
{
    int ID;
    Item *nextItem;
    Item *previousItem;
};

Item *addToSortedLinkedList(Item *p_list, int id);

void printList(Item *p_list);

int main()
{
    Item *p_items = nullptr;
    int IDs[10];
    IDs[0] = 5;
    IDs[1] = 15;
    IDs[2] = 0;
    IDs[3] = 12;
    IDs[4] = -1;
    IDs[5] = 2;
    IDs[6] = 8;
    IDs[7] = 100;
    IDs[8] = 100;
    IDs[9] = 55;
    cout << "The list of items starts with the following IDs...\n";
    for (int i = 0; i < 10; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << IDs[i];
    }
    cout << '\n';

    cout << "Create linked list of 10 items...\n";
    for (int i = 0; i < 10; i++)
    {
        p_items = addToSortedLinkedList(p_items, IDs[i]);
    }
    cout << '\n';

    cout << "Ordering the list...\n\n";
    printList(p_items);

    if (p_items != nullptr)
    {
        Item *p_current = p_items;
        Item *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->nextItem;
            delete p_current;
            p_current = p_next;
        }
    }
}
Item *addToSortedLinkedList(Item *p_list, int id)
{
    Item *p_item = new Item;
    p_item->ID = id;

    if (p_list == nullptr)
    {
        p_item->previousItem = nullptr;
        p_item->nextItem = nullptr;
        return p_item;
    }

    Item *p_current = p_list;
    Item *p_nextItem = p_list->nextItem;
    Item *p_previousItem = p_list->previousItem;
    while (p_current != nullptr)
    {
        if ( p_nextItem == nullptr && p_previousItem == nullptr )
        {
            if(p_item->ID >= p_current->ID)
            {
                p_item->previousItem = nullptr;
                p_item->nextItem = p_current;

                p_current->previousItem = p_item;
                return p_item;
            }
            else
            {
                p_item->previousItem = p_current;
                p_item->nextItem = nullptr;

                p_current->nextItem = p_item;
                return p_list;
            }
        }
        else if ( p_nextItem == nullptr && p_previousItem != nullptr)
        {
            if(p_item->ID >= p_current->ID)
            {
                p_item->previousItem = p_previousItem;
                p_item->nextItem = p_current;

                p_current->previousItem = p_item;
                p_previousItem->nextItem = p_item;
            }
            else
            {
                p_item->previousItem = p_current;
                p_item->nextItem = nullptr;

                p_current->nextItem = p_item;
            }
            return p_list;
        }
        else if ( p_nextItem != nullptr && p_previousItem == nullptr )
        {
            if (p_item->ID >= p_current->ID)
            {
                p_item->previousItem = nullptr;
                p_item->nextItem = p_current;

                p_current->previousItem = p_item;
                return p_item;
            }
            else
            {
                p_previousItem = p_current;
                p_current = p_nextItem;
                if (p_current != nullptr)
                {
                    p_nextItem = p_current->nextItem;
                }
                else
                {
                    p_nextItem = nullptr;
                }
            }
        }
        else if ( p_nextItem != nullptr && p_previousItem != nullptr )
        {
            if (p_item->ID >= p_current->ID && p_item->ID < p_previousItem->ID)
            {
                p_item->previousItem = p_previousItem;
                p_item->nextItem = p_current;

                p_current->previousItem = p_item;
                p_previousItem->nextItem = p_item;
                return p_list;
            }
            else
            {
                p_previousItem = p_current;
                p_current = p_nextItem;
                if (p_current != nullptr)
                {
                    p_nextItem = p_current->nextItem;
                }
                else
                {
                    p_nextItem = nullptr;
                }
            }
        }
    }
    return p_list;
}
void printList(Item *p_list)
{
    cout << "Printing the list...\n";

    Item *p_current = p_list;
    while (p_current != nullptr)
    {
        cout << "Item ID: " << p_current->ID << '\n';
        p_current = p_current->nextItem;
    }
    cout << '\n';
}
