#include <iostream>
#include <string>

using namespace std;

struct Disc
{
    int size = 0;
    Disc *next = nullptr;
    Disc *previous = nullptr;
};

Disc *getSmallestDisk(Disc *p_list);
int getSmallestDiskSize(Disc *p_list, Disc **p_smallest);

Disc *addNewToLinkedList(Disc *p_list, int size);
Disc *addToLinkedListBeginning(Disc *head, Disc *node);
Disc *addToLinkedListEnd(Disc *head, Disc *node);
Disc *removeFromLinkedList(Disc *p_list, Disc *p_item);

struct Discs
{
    Disc *head = nullptr;

    Disc *pop()
    {
        Disc *smallestDisk = getSmallestDisk(head);
        head = removeFromLinkedList(head, smallestDisk);
        return smallestDisk;
    }

    void push(Disc *disc)
    {
        head = addToLinkedListBeginning(head, disc);
    }
};

Discs *generatePegA(int size);
void moveDisc(int discSize, Discs *source, Discs *target, Discs *auxiliary);

void printList(Discs *p_list);
void printAllLists(Discs *pegA, Discs *pegB, Discs *pegC);

Discs *pegA;
Discs *pegB;
Discs *pegC;
int iteration = 0;

int main()
{
    const int minDiscSize = 2;
    int maxDiscSize = minDiscSize;
    do
    {
        cout << "Please enter the maximum disk size: ";
        cin >> maxDiscSize;
    }
    while (maxDiscSize < minDiscSize);

    pegA = generatePegA(maxDiscSize);
    pegB = new Discs;
    pegC = new Discs;

    printAllLists(pegA, pegB, pegC);

    cout << '\n';
    cout << "Solving the Tower of Hanoi Problem using recursion.\n\n";
    moveDisc(maxDiscSize, pegA, pegC, pegB);

    if (pegA->head != nullptr)
    {
        Disc *p_current = pegA->head;
        Disc *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->next;
            delete p_current;
            p_current = p_next;
        }
    }
    delete pegA;

    if (pegB->head != nullptr)
    {
        Disc *p_current = pegB->head;
        Disc *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->next;
            delete p_current;
            p_current = p_next;
        }
    }
    delete pegB;

    if (pegC->head != nullptr)
    {
        Disc *p_current = pegC->head;
        Disc *p_next;
        while (p_current != nullptr)
        {
            p_next = p_current->next;
            delete p_current;
            p_current = p_next;
        }
    }
    delete pegC;
}

Discs *generatePegA(int size)
{
    Disc *p_items = nullptr;
    for (int i = 1; i <= size; i++)
    {
        p_items = addNewToLinkedList(p_items, i);
    }

    Discs *pegA = new Discs;
    pegA->head = p_items;
    return pegA;
}

void moveDisc(int discSize, Discs *source, Discs *target, Discs *auxiliary)
{
    if (discSize > 0)
    {
        moveDisc(discSize - 1, source, auxiliary, target);

        target->push(source->pop());

        cout << "Iteration " << ++iteration;
        printAllLists(pegA, pegB, pegC);

        moveDisc(discSize - 1, auxiliary, target, source);
    }
}
Disc *getSmallestDisk(Disc *p_list)
{
    Disc *p_smallest = nullptr;

    getSmallestDiskSize(p_list, &p_smallest);

    return p_smallest;
}
int getSmallestDiskSize(Disc *p_list, Disc **p_smallest)
{
    Disc *p_current = p_list;
    Disc *p_temp;

    int minSize = p_current->size;
    p_temp = p_current;
    while (p_current != nullptr)
    {
        if (p_current->size < minSize)
        {
            minSize = p_current->size;
            p_temp = p_current;
        }
        p_current = p_current->next;
    }
    if (p_smallest != nullptr)
    {
        *p_smallest = p_temp;
    }
    return minSize;
}
Disc *addNewToLinkedList(Disc *p_list, int size)
{
    Disc *p_item = new Disc;
    p_item->size = size;

    return addToLinkedListEnd(p_list, p_item);
}
Disc *addToLinkedListEnd(Disc *head, Disc *node)
{
    if (head == nullptr)
    {
        node->previous = head;
        node->next = nullptr;
        return node;
    }
    else
    {
        Disc *temp = head;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = node;
        node->previous = temp;
        node->next = nullptr;
        return head;
    }
}
Disc *addToLinkedListBeginning(Disc *head, Disc *node)
{
    if (head == nullptr)
    {
        node->previous = nullptr;
        node->next = head;
        return node;
    }
    else
    {
        Disc *temp = head;
        node->previous = nullptr;
        node->next = temp;
        temp->previous = node;
        return node;
    }
}
Disc *removeFromLinkedList(Disc *p_list, Disc *p_item)
{
    Disc *p_next = p_item->next;
    Disc *p_previous = p_item->previous;
    p_item->next = nullptr;
    p_item->previous = nullptr;

    if (p_next == nullptr && p_previous == nullptr)
    {
        return nullptr;
    }

    if ( p_next != nullptr && p_previous == nullptr )
    {
        p_next->previous = p_previous;
        return p_next;
    }

    if (p_next == nullptr && p_previous != nullptr)
    {
        p_previous->next = p_next;
    }
    else if (p_next != nullptr && p_previous != nullptr)
    {
        p_previous->next = p_next;
        p_next->previous = p_previous;
    }

    while (p_previous->previous != nullptr)
    {
        p_previous = p_previous->previous;
    }

    return p_previous;
}
void printAllLists(Discs *pegA, Discs *pegB, Discs *pegC)
{
    cout << '\n';
    cout << "Peg A:\n";
    printList(pegA);
    cout << '\n';

    cout << "Peg B:\n";
    printList(pegB);
    cout << '\n';

    cout << "Peg C:\n";
    printList(pegC);
    cout << '\n';
}
void printList(Discs *p_list)
{
    if (p_list == nullptr || p_list->head == nullptr)
    {
        cout << "Disk peg is empty.\n";
        return;
    }

    cout << "Printing the list...\n";
    Disc *p_current = p_list->head;
    while (p_current != nullptr)
    {
        cout << "Disk Size: " << p_current->size << '\n';
        p_current = p_current->next;
    }
    cout << '\n';
}
