
#include <iostream>
#include <string>

using namespace std;

struct Item
{
    string name;
    Item *nextItem;
    Item *previousItem;
};

Item *addToLinkedList(Item *p_list, string name);
Item *getItemByName(Item *p_list, string name);

void printList(Item *p_list);

int main()
{
    Item *p_items = nullptr;
    Item *p_find = nullptr;
    string names[10];
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

    cout << "Create linked list of 10 items...\n";
    for (int i = 0; i < 10; i++)
    {
        p_items = addToLinkedList(p_items, names[i]);
    }
    printList(p_items);

    cout << "Getting element for " << names[3] << "...\n";
    p_find = getItemByName(p_items, names[3]);
    if (p_find != nullptr)
    {
        printList(p_find);
    }
    else
    {
        cout << "Can not find the matching node.\n\n";
    }

    cout << "Getting non-existing name...\n";
    p_find = getItemByName(p_items, "Carmen");
    if (p_find != nullptr)
    {
        printList(p_find);
    }
    else
    {
        cout << "Can not find the matching node.\n\n";
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

Item *addToLinkedList(Item *p_list, string name)
{
    Item *p_item = new Item;
    p_item->name = name;
    p_item->previousItem = nullptr;
    p_item->nextItem = p_list;
    if (p_list != nullptr)
    {
        p_list->previousItem = p_item;
    }

    return p_item;
}

Item *getItemByName(Item *p_list, string name)
{
    Item *p_current = p_list;
    while (p_current != nullptr)
    {
        if (p_current->name == name)
        {
            return p_current;
        }
        p_current = p_current->nextItem;
    }
    return nullptr;
}
void printList(Item *p_list)
{
    cout << "Printing the list...\n";

    Item *p_current = p_list;
    while (p_current != nullptr)
    {
        cout << "Item Name: " << p_current->name << '\n';
        p_current = p_current->nextItem;
    }
    cout << '\n';
}
