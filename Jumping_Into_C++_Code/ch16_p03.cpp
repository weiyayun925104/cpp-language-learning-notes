#include <iostream>
#include <string>

using namespace std;

struct Item
{
    string name;
    Item *next;
    Item *previous;
};

Item *addToLinkedList(Item *p_list, string name);
Item *createLinkedList(string names[], int namesSize);
Item *createLinkedListRecursive(string names[], int namesSize, int nameIndex);
Item *removeCurrentFromLinkedList(Item *p_list, Item *p_current);
Item *removeFromLinkedList(Item *p_list, string name);
void removeFromLinkedListRecursive(Item *p_list, string name, Item **p_head);
void printList(Item *p_list);

int main()
{
    const int namesSize = 10;
    string names[namesSize];
    names[0] = "Sam";
    names[1] = "Sally";
    names[2] = "Sue";
    names[3] = "Mark";
    names[4] = "Phil";
    names[5] = "Brenton";
    names[6] = "Melissa";
    names[7] = "Charles";
    names[8] = "Quigly";
    names[9] = "Foo";


    cout << "Create linked list of " << namesSize << " items with a loop...\n";
    Item *p_items = createLinkedList(names, namesSize);
    printList(p_items);

    int const indexRemove = 5;
    cout << "Removing item " << indexRemove << ": " << names[indexRemove] << " from linked list with a loop...\n";
    p_items = removeFromLinkedList(p_items, names[indexRemove]);
    printList(p_items);

    if (p_items != nullptr)
    {
        Item *p_current = p_items;
        Item *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->next;
            delete p_current;
            p_current = p_next;
        }
    }

    cout << "Create linked list of " << namesSize << " items with a recursion...\n";
    Item *p_itemsRecursion = createLinkedListRecursive(names, namesSize, namesSize - 1);
    printList(p_itemsRecursion);

    cout << "Removing item " << indexRemove << ": " << names[indexRemove] << " from linked list with a recursion...\n";
    removeFromLinkedListRecursive(p_itemsRecursion, names[indexRemove], &p_itemsRecursion);
    printList(p_itemsRecursion);

    if (p_itemsRecursion != nullptr)
    {
        Item *p_current = p_itemsRecursion;
        Item *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->next;
            delete p_current;
            p_current = p_next;
        }
    }
}


Item *createLinkedList(string names[], int namesSize)
{
    Item *p_items = nullptr;
    for (int i = 0; i < namesSize; i++)
    {
        p_items = addToLinkedList(p_items, names[i]);
    }
    return p_items;
}

Item *createLinkedListRecursive(string names[], int namesSize, int nameIndex)
{
    Item *p_items = nullptr;
    if (nameIndex > 0 && nameIndex < namesSize)
    {
        p_items = createLinkedListRecursive(names, namesSize, nameIndex - 1);
    }

    if(nameIndex >= 0 && nameIndex < namesSize)
    {
        p_items = addToLinkedList(p_items, names[nameIndex]);
    }

    return p_items;
}

Item *addToLinkedList(Item *p_list, string name)
{
    Item *p_item = new Item;
    p_item->name = name;
    p_item->previous = nullptr;
    p_item->next = p_list;
    if (p_list != nullptr)
    {
        p_list->previous = p_item;
    }
    return p_item;
}

Item *removeFromLinkedList(Item *p_list, string name)
{
    Item *p_current = p_list;
    while (p_current != nullptr)
    {
        if (p_current->name == name)
        {
            return removeCurrentFromLinkedList(p_list, p_current);
        }
        p_current = p_current->next;
    }
    return p_list;
}
void removeFromLinkedListRecursive(Item *p_list, string name, Item **p_head)
{
    Item *p_current = p_list;
    if(p_current != nullptr)
    {
        if (p_current->name == name)
        {
            *p_head = removeCurrentFromLinkedList(*p_head, p_current);
            return;
        }
        removeFromLinkedListRecursive(p_current->next, name, p_head);
    }
}
Item *removeCurrentFromLinkedList(Item *p_list, Item *p_current)
{
    Item *p_previous = p_current->previous;
    Item *p_next = p_current->next;

    if (p_current == p_list)
    {
        if (p_next != nullptr)
       {
            p_next->previous = p_previous;
        }
        delete p_current;
        return p_next;
    }
    else
    {
        p_previous->next = p_next;
        if (p_next != nullptr)
       {
            p_next->previous = p_previous;
        }
        delete p_current;
        return p_list;
    }
}
void printList(Item *p_list)
{
    cout << "Printing the list...\n";

    Item *p_current = p_list;
    while (p_current != nullptr)
    {
        cout << "Item Name: " << p_current->name << '\n';
        p_current = p_current->next;
    }
    cout << '\n';
}
