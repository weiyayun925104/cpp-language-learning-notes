#include <cstdlib>
#include "queue.h"

Queue::Queue(int qs) : qsize(qs)
{
    front = rear = NULL;
    items = 0;
}

Queue::~Queue()
{
    Node *next;
    while (front != NULL)
    {
        next = front->next;
        delete front;
        front = next;
    }
}

bool Queue::isempty() const
{
    return items == 0;
}

bool Queue::isfull() const
{
    return items == qsize;
}

int Queue::queuecount() const
{
    return items;
}
bool Queue::enqueue(const Item &item)
{
    if (isfull())
    {
        return false;
    }
    Node *add = new Node;

    add->item = item;
    add->next = NULL;
    if (items == 0)
    {
        front = add;
        rear = add;
    }
    else
    {
        rear->next = add;
        rear = add;
    }
    items++;
    return true;
}
bool Queue::dequeue(Item &item)
{
    if (isempty())
    {
        return false;
    }
    item = front->item;
    items--;
    Node *next = front->next;
    delete front;
    front = next;
    if (items == 0)
    {
        front = NULL;
        rear = NULL;
    }
    return true;
}
void Customer::set(long when)
{
    processtime = std::rand() % 3 + 1;
    arrive = when;
}
