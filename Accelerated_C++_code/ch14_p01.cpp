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
#include <cstring>

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
using std::runtime_error;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

template <typename T>
class Handle
{
public:
    Handle() : p(nullptr) { }
    Handle(T *t) : p(t) { }
    Handle(const Handle<T> &s) : p(nullptr)
    {
        if (s.p != nullptr)
        {
            p = s.p->clone();
        }
    }

    Handle<T> &operator=(const Handle<T> &);
    ~Handle()
    {
        delete p;
    }

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const;
    T *operator->() const;

private:
    T *p;
};

template<typename T>
Handle<T> &Handle<T>::operator=(const Handle<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    delete p;
    p = rhs.p != nullptr ? rhs.p->clone() : nullptr;
    return *this;
}

template <typename T>
T &Handle<T>::operator*() const
{
    if (p != nullptr)
    {
        return *p;
    }
    throw runtime_error("unbound Handle");
}

template <typename T>
T *Handle<T>::operator->() const
{
    if (p != nullptr)
    {
        return p;
    }
    throw runtime_error("unbound Handle");
}

template <typename T>
class Ref_handle
{
public:
    Ref_handle() : refptr(new size_t(1)), p(nullptr) { }
    Ref_handle(T *t) : refptr(new size_t(1)), p(t) { }

    Ref_handle(const Ref_handle<T> &h) : refptr(h.refptr), p(h.p)
    {
        ++*refptr;
    }

    Ref_handle<T> &operator=(const Ref_handle<T> &);

    ~Ref_handle();

    operator bool() const
    {
        return p != nullptr;
    }
    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ref_handle");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ref_handle");
    }

private:
    T *p;
    size_t *refptr;
};

template<typename T>
Ref_handle<T> &Ref_handle<T>::operator=(const Ref_handle<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.refptr;

    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }

    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template<typename T>
Ref_handle<T>::~Ref_handle()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

class Ref_counter
{
public:
    Ref_counter() : counter(new size_t(1)) { };
    Ref_counter(size_t s) : counter(new size_t(s)) { };
    Ref_counter(const Ref_counter &r) : counter(r.counter) { };

    Ref_counter &operator=(const Ref_counter &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        if (*counter <= 0)
        {
            delete counter;
        }
        counter = rhs.counter;
        return *this;
    };

    Ref_counter &operator++()
    {
        (*counter)++;
        return *this;
    };

    Ref_counter &operator--()
    {
        (*counter)--;
        return *this;
    };

    Ref_counter operator++(int)
    {
        Ref_counter ret(*(this->counter));
        (*counter)++;
        return ret;
    };

    Ref_counter operator--(int)
    {
        Ref_counter ret(*(this->counter));
        (*counter)--;
        return ret;
    };

    ~Ref_counter()
    {
        if (*counter <= 0)
        {
            delete counter;
        }
    };

    size_t count()
    {
        return *counter;
    };

private:
    size_t *counter;
};


template<typename T>
T *clone(const T *tp)
{
    return tp->clone();
}

template<typename T>
class Ptr
{
public:
    Ptr() : refptr(new size_t(1)), p(nullptr) { }
    Ptr(T *t) : refptr(new size_t(1)), p(t) { }
    Ptr(const Ptr<T> &h) : refptr(h.refptr), p(h.p)
    {
        ++*refptr;
    }

    Ptr<T> &operator=(const Ptr<T> &);
    ~Ptr();

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ptr");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ptr");
    }

    void make_unique()
    {
        if (*refptr > 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p != nullptr ? clone(p) : nullptr;
        }
    }

private:
    T *p;
    size_t *refptr;
};

template<typename T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.refptr;
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template<typename T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

template<typename T>
class Ptr_r
{
public:
    Ptr_r() : p(nullptr) { }
    Ptr_r(T *t) : p(t) { }
    Ptr_r(const Ptr_r<T> &h) : ref_c(h.ref_c), p(h.p)
    {
        ++ref_c;
    }

    Ptr_r<T> &operator=(const Ptr_r<T> &);
    ~Ptr_r();

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ptr_r");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ptr_r");
    }

    void make_unique()
    {
        if (ref_c.count() > 1)
        {
            --ref_c;
            ref_c = Ref_counter();
            p = p != nullptr ? clone(p) : nullptr;
        }
    }

private:
    T *p;
    Ref_counter ref_c;
};

template<typename T>
Ptr_r<T> &Ptr_r<T>::operator=(const Ptr_r<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if ((--ref_c).count() == 0)
    {
        delete p;
    }
    ref_c = rhs.ref_c;
    p = rhs.p;
    ++ref_c;
    return *this;
}

template<typename T>
Ptr_r<T>::~Ptr_r()
{
    if ((--ref_c).count() == 0)
    {
        delete p;
    }
}

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
    template<typename In>
    Vec(In b, In e)
    {
        create(b, e);
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
    void clear()
    {
        destroy();
    };
    iterator erase(iterator it)
    {
        return destroy(it);
    };
    iterator erase(iterator b, iterator e)
    {
        return destroy(b, e);
    };

    template <typename In>
    void insert(iterator position, In first, In last)
    {
        insert_elements(position, first, last);
    };

    template <typename In>
    void assign(In first, In last)
    {
        assign_elements(first, last);
    };

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    template<typename In>
    void create(In, In);

    void uncreate();

    void grow(bool);

    void unchecked_append(const T &);

    void destroy();
    iterator destroy(iterator);
    iterator destroy(iterator, iterator);

    template <typename In>
    void insert_elements(iterator, In, In);

    template <typename In>
    void assign_elements(In, In);
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

template<typename T>
template<typename In>
void Vec<T>::create(In b, In e)
{
    data = alloc.allocate(e - b);
    limit = avail = std::uninitialized_copy(b, e, data);
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

template <typename T>
void Vec<T>::destroy()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
    }
    avail = data;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator pos)
{
    if (data != nullptr && pos != avail)
    {
        alloc.destroy(pos);
        iterator it = pos + 1;

        while (it != avail)
        {
            alloc.construct(pos++, *it++);
            alloc.destroy(pos);
        }
        avail = pos;
    }
    return avail;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator b, iterator e)
{
    if (data != nullptr && b != avail && b != e)
    {
        iterator it = b;
        while (it != e)
        {
            alloc.destroy(it++);
        }

        while (e != avail)
        {
            alloc.construct(b++, *e);
            alloc.destroy(e++);
        }

        avail = b;
    }
    return avail;
}

template <typename T>
template <typename In>
void Vec<T>::insert_elements(iterator pos, In first, In last)
{
    Vec<T> tail(pos, avail);

    destroy(pos, avail);

    In iter1 = first;

    while (iter1 != last)
    {
        push_back(*iter1++);
    }

    iterator iter2 = tail.begin();

    while (iter2 != tail.end())
    {
        push_back(*iter2++);
    }
}

template <typename T>
template <typename In>
void Vec<T>::assign_elements(In first, In last)
{
    uncreate();
    create(first, last);
}

template<>
inline Vec<char> *clone< Vec<char> >(const Vec<char> *vp)
{
    return new Vec<char>(*vp);
}

class Str
{
public:
    typedef Vec<char>::size_type size_type;
    typedef Vec<char>::iterator iterator;
    typedef Vec<char>::const_iterator const_iterator;

    Str() : data(new Vec<char>) { }
    Str(size_type n, char c) : data(new Vec<char>(n, c)) { }
    Str(const char *cp) : data(new Vec<char>)
    {
        copy(cp, cp + strlen(cp), back_inserter(*data));
    }
    template<class In>
    Str(In b, In e) : data(new Vec<char>(b, e)) { }

    size_type size() const
    {
        return data->size();
    }

    char &operator[](size_type i)
    {
        data.make_unique();
        return (*data)[i];
    }

    const char &operator[](size_type i) const
    {
        return (*data)[i];
    }

    Str &operator+=(const Str &s)
    {
        data.make_unique();
        copy(s.data->begin(), s.data->end(), back_inserter(*data));
        return *this;
    }

    iterator begin()
    {
        return data->begin();
    };
    const_iterator begin() const
    {
        return data->begin();
    };
    iterator end()
    {
        return data->end();
    };
    const_iterator end() const
    {
        return data->end();
    };

    friend istream &operator >> (istream &is, Str &s)
    {
        s.data->clear();
        char c;
        while (is.get(c) && isspace(c))
            ;
        if (is)
        {
            do
            {
                s.data->push_back(c);
            }
            while (is.get(c) && !isspace(c));
            if (is)
            {
                is.unget();
            }
        }
        return is;
    }

    friend ostream &operator<< (ostream &os, const Str &s)
    {
        for (Str::size_type i = 0; i != s.size(); ++i)
        {
            os << s[i];
        }
        return os;
    }

    friend Str operator+(const Str &l, const Str &r)
    {
        Str ret = l;
        ret += r;
        return ret;
    }

private:
    Ptr< Vec<char> > data;
};

double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
    {
        throw domain_error("Student has done no homework");
    }
    return grade(midterm, final, median(hw));
}

istream &read_hw(istream &is, vector<double> &hw)
{
    if (is)
    {
        double x;
        while (is >> x)
        {
            hw.push_back(x);
        }

        is.clear();
        while (is.get() != '\n')
        {
            continue;
        }
    }

    return is;
}

class Core
{
public:
    friend class Student_info;
    friend class Audit;
    Core() : midterm(0), final(0)
    {
        cerr << "constructor Core()" << endl;
    }
    Core(istream &is)
    {
        cerr << "constructor Core(istream &is)" << endl;
        read(is);
    }

    virtual ~Core()
    {
        cerr << "destructor ~Core()" << endl;
    }

    const string &name() const
    {
        return _name;
    }
    virtual double grade() const
    {
        return ::grade(midterm, final, homework);
    }
    string letter_grade() const;
    virtual istream &read(istream &);

    bool valid() const
    {
        return !homework.empty();
    }
    virtual bool requirements_met() const
    {
        return find(homework.begin(), homework.end(), 0.0) == homework.end();
    }
    virtual Core *clone() const
    {
        return new Core(*this);
    }

protected:
    istream &read_common(istream &in)
    {
        in >> _name >> midterm >> final;
        return in;
    }
    double midterm, final;
    vector<double> homework;

private:
    string _name;
};

istream &Core::read(istream &in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

string Core::letter_grade() const
{
    static const double numbers[] =
    {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    static const char *const letters[] =
    {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

    double result = grade();

    for (size_t i = 0; i < ngrades; ++i)
    {
        if (result >= numbers[i])
        {
            return letters[i];
        }
    }
    return "?\?\?";
}

inline bool compare(const Core &c1, const Core &c2)
{
    return c1.name() < c2.name();
}

inline bool compare_Core_ptrs(const Core *cp1, const Core *cp2)
{
    return compare(*cp1, *cp2);
}

class Grad : public Core
{
public:
    Grad() : thesis(0.0)
    {
        cerr << "constructor Grad()" << endl;
    }
    Grad(istream &is)
    {
        cerr << "constructor Grad(istream &is)" << endl;
        read(is);
    }

    ~Grad()
    {
        cerr << "destructor ~Grad()" << endl;
    }
    double grade() const;
    istream &read(istream &);

    bool requirements_met() const
    {
        return Core::requirements_met() && thesis != 0.0;
    }
    Grad *clone() const
    {
        return new Grad(*this);
    }

protected:

private:
    double thesis;
};

istream &Grad::read(istream &in)
{
    Core::read_common(in);
    in >> Grad::thesis;
    read_hw(in, Core::homework);
    return in;
}

double Grad::grade() const
{
    return min(Core::grade(), Grad::thesis);
}

class Credit : public Core
{
public:
    Credit() {}
    Credit(istream &is) : Core(is) {}

    double grade() const;
    bool passed() const
    {
        return grade() >= 60;
    }

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }
    Credit *clone() const
    {
        return new Credit(*this);
    }

protected:
};

double Credit::grade() const
{
    if (Core::homework.empty())
    {
        return (midterm + final) / 2.0;
    }
    else
    {
        return Core::grade();
    }
}

class Audit : public Core
{
public:
    Audit() {}
    Audit(istream &is)
    {
        read(is);
    }

    istream &read(istream &in)
    {
        in >> _name;
        return in;
    }

    double grade() const
    {
        return 0.0;
    };

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }
    Audit *clone() const
    {
        return new Audit(*this);
    }

protected:
};

class Student_info
{
public:
    Student_info() { }
    Student_info(istream &is)
    {
        read(is);
    }

    istream &read(istream &);

    const string &name() const
    {
        if (cp)
        {
            return cp->name();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

    double grade() const
    {
        if (cp)
        {
            return cp->grade();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

private:
    Handle<Core> cp;
};

istream &Student_info::read(istream &is)
{
    char ch;
    cout << "Enter U for new Core, C for new Credit, A for new Audit, G for new Grad" << endl;
    if (is >> ch)
    {
        if (ch == 'U')
        {
            cout << "new Core" << endl;
            cp = new Core(is);
        }
        else if (ch == 'C')
        {
            cout << "new Credit" << endl;
            cp = new Credit(is);
        }
        else if (ch == 'A')
        {
            cout << "new Audit" << endl;
            cp = new Audit(is);
        }
        else
        {
            cout << "new Grad" << endl;
            cp = new Grad(is);
        }
    }
    return is;
}

inline bool compare_info(const Student_info &s1, const Student_info &s2)
{
    return s1.name() < s2.name();
}

class Student_info_p
{
public:
    Student_info_p() { }
    Student_info_p(istream &is)
    {
        read(is);
    }

    istream &read(istream &);

    const string &name() const
    {
        if (cp)
        {
            return cp->name();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

    double grade() const
    {
        if (cp)
        {
            return cp->grade();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

private:
    Ptr<Core> cp;
};

istream &Student_info_p::read(istream &is)
{
    char ch;
    cout << "Enter U for new Core, C for new Credit, A for new Audit, G for new Grad" << endl;
    if (is >> ch)
    {
        if (ch == 'U')
        {
            cout << "new Core" << endl;
            cp = new Core(is);
        }
        else if (ch == 'C')
        {
            cout << "new Credit" << endl;
            cp = new Credit(is);
        }
        else if (ch == 'A')
        {
            cout << "new Audit" << endl;
            cp = new Audit(is);
        }
        else
        {
            cout << "new Grad" << endl;
            cp = new Grad(is);
        }
    }
    return is;
}

inline bool compare_info_p(const Student_info_p &s1, const Student_info_p &s2)
{
    return s1.name() < s2.name();
}

inline bool compare_Core_handles(const Handle<Core> hc1, const Handle<Core> hc2)
{
    return compare(*hc1, *hc2);
}

inline bool compare_Core_Ptr(const Ptr<Core> hc1, const Ptr<Core> hc2)
{
    return compare(*hc1, *hc2);
}

int main()
{
    Ptr<Core> p1 = new Core(cin);
    Ptr<Core> p2 = new Grad(cin);

    cout << p1->name() << ", " << p1->grade() << endl;
    cout << p2->name() << ", " << p2->grade() << endl;
    cout << "compare_Core_Ptr(p1, p2) = " << compare_Core_Ptr(p1, p2) << endl;

    return 0;
}
