#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

template <typename T>
struct Node
{
    T data;
    Node<T> *previous;
    Node<T> *next;

    Node() : data(T()), previous(nullptr), next(nullptr) {};
    Node(const T &d) : data(d), previous(nullptr), next(nullptr) {};
};

template <typename T>
class NodeIterator
{
public:
    NodeIterator(Node<T> *ptr) : node_ptr(ptr) {};

    NodeIterator &operator++();
    NodeIterator &operator--();
    NodeIterator  operator++(int);
    NodeIterator  operator--(int);
    bool operator!=(const NodeIterator &) const;
    T &operator*() const;

private:
    Node<T> *node_ptr;
};

template <typename T>
NodeIterator<T> &NodeIterator<T>::operator++()
{
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
NodeIterator<T> &NodeIterator<T>::operator--()
{
    node_ptr = node_ptr->previous;
    return *this;
}

template <typename T>
NodeIterator<T> NodeIterator<T>::operator++(int)
{
    NodeIterator<T> ret(this->node_ptr);
    node_ptr = node_ptr->next;
    return ret;
}

template <typename T>
NodeIterator<T> NodeIterator<T>::operator--(int)
{
    NodeIterator<T> ret(this->node_ptr);
    node_ptr = node_ptr->previous;
    return ret;
}

template <typename T>
bool NodeIterator<T>::operator!=(const NodeIterator &rhs) const
{
    return this->node_ptr != rhs.node_ptr;
}

template <typename T>
T &NodeIterator<T>::operator*() const
{
    return node_ptr->data;
}

template <typename T>
class LList
{
public:
    typedef NodeIterator<T> iterator;
    typedef const NodeIterator<T> const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    LList() : front(nullptr), back(nullptr), _size(0) {}
    explicit LList(size_type n, const T &val = T()) : front(nullptr), back(nullptr), _size(0)
    {
        create(n, val);
    }
    LList(const LList &l) : front(nullptr), back(nullptr), _size(0)
    {
        create(l.begin(), l.end());
    }

    LList &operator=(const LList &);
    ~LList()
    {
        uncreate();
    }

    void push_back(const T &val)
    {
        append(val);
    }

    size_type size() const
    {
        return _size;
    }
    iterator begin()
    {
        return iterator(front);
    }
    const_iterator begin() const
    {
        return iterator(front);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator end() const
    {
        return iterator(nullptr);
    }

private:
    Node<T> *front;
    Node<T> *back;
    size_type _size;

    void create(size_type, const T &);
    void create(iterator, iterator);
    void append(const T &);
    void uncreate();

};

template <typename T>
LList<T> &LList<T>::operator=(const LList &l)
{
    if (this == &l)
    {
        return *this;
    }
    uncreate();
    create(l.begin(), l.end());
    return *this;
}

template <typename T>
void LList<T>::create(size_type n, const T &val)
{
    for (size_type i = 0; i < n; i++)
    {
        append(val);
    }
}

template <typename T>
void LList<T>::create(iterator b, iterator e)
{
    while (b != e)
    {
        append(*b++);
    }
}

template <typename T>
void LList<T>::append(const T &val)
{
    Node<T> *node = new Node<T>(val);

    if (_size == 0)
    {
        front = back = node;
    }
    else if (_size == 1)
    {
        node->previous = front;
        front->next = node;
        back = node;
    }
    else
    {
        node->previous = back;
        back->next = node;
        back = node;
    }

    _size++;
}

template <typename T>
void LList<T>::uncreate()
{
    Node<T> *node = back;

    while (node != nullptr)
    {
        Node<T> *node_delete = node;
        node = node->previous;
        delete node_delete;
    }

    front = back = nullptr;
    _size = 0;
}

int main()
{
    LList<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    LList<int>::iterator iter = list.begin();

    cout << *++iter << endl;
    cout << *--iter << endl;

    while (iter != list.end())
    {
        cout << *iter++ << endl;
    }

    LList<string> stringlist(5, "test");
    LList<string> stringlist_copy = stringlist;
    LList<string>::iterator listIter = stringlist.begin();

    *listIter = "first";

    while (listIter != stringlist.end())
    {
        cout << *listIter++ << endl;
    }

    if (stringlist_copy.size() > 0)
    {
        listIter = stringlist_copy.begin();
        while (listIter != stringlist.end())
        {
            cout << *listIter++ << endl;
        }
    }

    return 0;
}
