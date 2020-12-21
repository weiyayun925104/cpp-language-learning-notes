#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <utility>
#include <random>
#include <limits>
#include <type_traits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include<climits>
#include <ctime>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::vector;
using std::list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;
using std::ios_base;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::numeric_limits;
using std::common_type;
using std::reverse;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
}

template<typename T>
ostream &print_vector(const vector<T> &v, ostream &os)
{
    if (v.size() > 0)
    {
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << endl;
    }

    return os;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}

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

int main(int argc, const char *argv[])
{
    try
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

        return 0;
    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        return 2;
    }
}
