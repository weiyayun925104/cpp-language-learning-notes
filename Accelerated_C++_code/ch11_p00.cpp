#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

template <typename T>
class Vec
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec()
    {
        create();
    }
    explicit Vec(size_type n, const T &val = T())
    {
        create(n, val);
    }
    Vec(const Vec<T> &v)
    {
        create(v.begin(), v.end());
    }

    Vec &operator=(const Vec<T> &);
    ~Vec()
    {
        uncreate();
    }
    T &operator[](size_type i)
    {
        return data[i];
    }
    const T &operator[](size_type i) const
    {
        return data[i];
    }

    void push_back(const T &val, bool double_grow = true)
    {
        if (avail == limit)
        {
            grow(double_grow);
        }
        unchecked_append(val);
    }

    size_type size() const
    {
        return avail - data;
    }
    iterator begin()
    {
        return data;
    }
    const_iterator begin() const
    {
        return data;
    }
    iterator end()
    {
        return avail;
    }
    const_iterator end() const
    {
        return avail;
    }

    ostream &print_vec(ostream &);

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow(bool);

    void unchecked_append(const T &);
};

template <typename T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

template <typename T>
void Vec<T>::create(size_type n, const T &val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <typename T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <typename T>
void Vec<T>::uncreate()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    uncreate();
    create(rhs.begin(), rhs.end());
    return *this;
}

template <typename T>
void Vec<T>::grow(bool double_grow)
{
    size_type new_size;

    if (double_grow)
    {
        new_size = max(2 * (limit - data), ptrdiff_t(1));
    }
    else
    {
        new_size = (limit - data) + 1;
    }

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}

template<typename T>
std::ostream &Vec<T>::print_vec(std::ostream &os)
{
    if (avail - data > 0)
    {
        iterator iter = data;

        os << *iter++;

        while (iter != avail)
        {
            os << ", " << *iter++;
        }

        os << std::endl;
    }
    return os;
}


int main()
{
    Vec<int> v1(5, 5);
    Vec<int> v2;

    v2 = v1;

    for (Vec<int>::size_type i = 2; i < v1.size(); i++)
    {
        v1[i] = 7;
    }

    for (Vec<int>::size_type i = 0; i < 10; i++)
    {
        v2.push_back(10);
    }

    v1.print_vec(cout);
    v2.print_vec(cout);

    return 0;
}
