#include <iostream>

using namespace std;

struct Item
{
    int ID;
    Item *nextItem;
    Item *previousItem;
};

Item *addToLinkedList(Item *p_list, int id);
Item *removeFromLinkedListWithTwoPointers(Item *p_item);
Item *removeFromLinkedListWithSinglePointer(Item *p_head, int target);

void printList(Item *p_list);

int main()
{
    Item *p_items = nullptr;
    Item *p_itemRemove = nullptr;
    Item *p_itemFirst = nullptr;
    Item *p_itemLast = nullptr;

    cout << "Create linked list of 10 items...\n";
    for (int i = 0; i < 10; i++)
    {
        p_items = addToLinkedList(p_items, i);
        if (i == 0)
        {
            p_itemFirst = p_items;
        }
        if (i == 5)
        {
            p_itemRemove = p_items;
        }
        if (i == 9)
        {
            p_itemLast = p_items;
        }
    }

    cout << "Remove ID 5 from the list\n";
    p_items = removeFromLinkedListWithTwoPointers(p_itemRemove);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }
    delete p_itemRemove;

    cout << "Remove ID 0 from the list\n";
    p_items = removeFromLinkedListWithTwoPointers(p_itemFirst);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }
    delete p_itemFirst;


    cout << "Remove ID 9 from the list\n";
    p_items = removeFromLinkedListWithTwoPointers(p_itemLast);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }
    delete p_itemLast;


    cout << "Remove ID 2 from the list\n";
    p_items = removeFromLinkedListWithSinglePointer(p_items, 2);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }

    cout << "Remove ID 12 from the list\n";
    p_items = removeFromLinkedListWithSinglePointer(p_items, 12);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }

    cout << "Remove ID 1 from the list\n";
    p_items = removeFromLinkedListWithSinglePointer(p_items, 1);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }

    cout << "Remove ID 8 from the list\n";
    p_items = removeFromLinkedListWithSinglePointer(p_items, 8);
    if (p_items != nullptr)
    {
        printList(p_items);
    }
    else
    {
        cout << "The list is empty.\n\n";
    }

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

Item *addToLinkedList(Item *p_list, int id)
{
    Item *p_item = new Item;
    p_item->ID = id;
    p_item->previousItem = nullptr;
    p_item->nextItem = p_list;
    if (p_list != nullptr)
    {
        p_list->previousItem = p_item;
    }

    return p_item;
}

Item *removeFromLinkedListWithTwoPointers(Item *p_item)
{
    Item *p_nextItem = p_item->nextItem;
    Item *p_previousItem = p_item->previousItem;

    if (p_nextItem == nullptr && p_previousItem == nullptr)
    {
        p_item->nextItem = nullptr;
        p_item->previousItem = nullptr;
        return nullptr;
    }

    if (p_nextItem == nullptr && p_previousItem != nullptr)
    {
        p_previousItem->nextItem = nullptr;

        while (p_previousItem->previousItem != nullptr)
        {
            p_previousItem = p_previousItem->previousItem;
        }

        p_item->nextItem = nullptr;
        p_item->previousItem = nullptr;
        return p_previousItem;
    }


    if (p_previousItem == nullptr && p_nextItem != nullptr)
    {
        p_nextItem->previousItem = nullptr;
    }
    else if (p_previousItem != nullptr && p_nextItem != nullptr)
    {
        p_previousItem->nextItem = p_nextItem;
        p_nextItem->previousItem = p_previousItem;
    }

    while (p_nextItem->previousItem != nullptr)
    {
        p_nextItem = p_nextItem->previousItem;
    }

    p_item->nextItem = nullptr;
    p_item->previousItem = nullptr;
    return p_nextItem;
}

Item *removeFromLinkedListWithSinglePointer(Item *p_head, int target)
{
    Item *p_current = p_head;
    Item *p_previous = nullptr;
    Item *p_next = nullptr;

    while (p_current != nullptr && p_current->ID != target)
    {
        p_previous = p_current;
        p_current = p_current->nextItem;
    }

    if (p_current == nullptr)
    {
        cout << target << " is not in the list.\n";
        return p_head;
    }

    if (p_current == p_head)
    {
        p_head = p_current->nextItem;
        if (p_head != nullptr)
        {
            p_head->previousItem = nullptr;
        }
    }
    else
    {
        p_next = p_current->nextItem;
        p_previous->nextItem = p_next;
        if (p_next != nullptr)
        {
            p_next->previousItem = p_previous;
        }
    }
    p_current->nextItem = nullptr;
    p_current->previousItem = nullptr;

    delete p_current;

    return p_head;
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
