#ifndef QUEUETP2_H_
#define QUEUETP2_H_

template <typename T>
class QueueTP
{
private:
    enum { Q_SIZE = 10 };
    class Node
    {
    public:
        T item;
        Node *next;
        Node(const T &i) : item(i), next(nullptr) { }
    };
    Node *front;
    Node *rear;
    int items;
    const int qsize;
    QueueTP(const QueueTP &q) : qsize(0) {}
    QueueTP &operator=(const QueueTP &q)
    {
        return *this;
    }
public:
    QueueTP(int qs = Q_SIZE);
    ~QueueTP();
    bool isempty() const
    {
        return items == 0;
    }
    bool isfull() const
    {
        return items == qsize;
    }
    int queuecount() const
    {
        return items;
    }
    bool enqueue(const T &item);
    bool dequeue(T &item);
};

template <typename T>
QueueTP<T>::QueueTP(int qs) : qsize(qs)
{
    front = rear = nullptr;
    items = 0;
}

template <typename T>
QueueTP<T>::~QueueTP()
{
    Node *next;
    while (front != nullptr)
    {
        next = front->next;
        delete front;
        front = next;
    }
}
template <typename T>
bool QueueTP<T>::enqueue(const T &item)
{
    if (isfull())
    {
        return false;
    }
    Node *add = new Node(item);
    if (isempty())
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

template <typename T>
bool QueueTP<T>::dequeue(T &item)
{
    if (isempty())
    {
        return false;
    }
    item = front->item;
    Node *next = front->next;
    delete front;
    front = next;
    items--;
    if (items == 0)
    {
        front = rear = nullptr;
    }
    return true;
}

#endif
