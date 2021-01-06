#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
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
#include <initializer_list>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
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
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::istream_iterator;
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
using std::streampos;
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
using std::ios;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::right;
using std::flush;
using std::numeric_limits;
using std::common_type;
using std::reverse;
using std::begin;
using std::end;
using std::initializer_list;
using std::function;
using std::bind;
using std::out_of_range;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::uninitialized_copy_n;
using std::uninitialized_fill_n;
using std::make_shared;
using std::make_unique;

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

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(const int &min, const int &max)
{
    return std::uniform_int_distribution<int> {min, max}(gen);
}

class TreeNode
{
public:
    TreeNode() : count(0), left(nullptr), right(nullptr), use(new std::size_t(1)) {}
    TreeNode(const std::string &s) : value(s), count(1), left(nullptr), right(nullptr), use(new std::size_t(1)) {}
    TreeNode(const TreeNode &tp):
        value(tp.value), count(tp.count), left(tp.left), right(tp.right), use(tp.use)
    {
        ++*use;
    }
    TreeNode &operator=(const TreeNode &);
    std::ostream &read(std::ostream &os) const
    {
        os << value << "\t" << count;
        return os;
    }
    void write(const std::string &str)
    {
        value = str;
    }
    ~TreeNode();
private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
    std::size_t *use;
};
TreeNode &TreeNode::operator=(const TreeNode &tp)
{
    if (this == &tp)
    {
        return *this;
    }
    ++*tp.use;
    if(--*use == 0)
    {
        if(left)
            delete left;
        if(right)
            delete right;
        delete use;
    }
    value = tp.value;
    count = tp.count;
    left = tp.left;
    right = tp.right;
    use = tp.use;
    return *this;
}
TreeNode::~TreeNode()
{
    if(--*use == 0)
    {
        if(left)
        {
            delete left;
            left = nullptr;
        }
        if(right)
        {
            delete right;
            right = nullptr;
        }
        delete use;
    }
}

class BinStrTree
{
public:
    BinStrTree() : root(new TreeNode()), use(new std::size_t(1)) {}
    BinStrTree(const BinStrTree &bp) : root(bp.root), use(bp.use)
    {
        ++*use;
    }
    BinStrTree &operator=(const BinStrTree &bp);
    ~BinStrTree();
private:
    TreeNode *root;
    std::size_t *use;
};
BinStrTree &BinStrTree::operator=(const BinStrTree &bp)
{
    if (this == &bp)
    {
        return *this;
    }
    ++*bp.use;
    if(--*use == 0)
    {
        delete root;
        delete use;
    }
    root = bp.root;
    use = bp.use;
    return *this;
}
BinStrTree::~BinStrTree()
{
    if(--*use == 0)
    {
        delete root;
        delete use;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        TreeNode t1("t1");
        TreeNode t2 = t1;
        t1.read(cout) << endl;
        t2.write("t2");
        t2.read(cout) << endl;
        {
            TreeNode t3(t2);
            t3.read(cout) << endl;
            t3.write("t3");
            t3.read(cout) << endl;;
        }
        TreeNode t4("t4");
        TreeNode t5("t5");
        t4.read(cout) << endl;;
        t5.read(cout) << endl;
        t4 = t4;
        t4.read(cout) << endl;;
        BinStrTree r1;
        BinStrTree r2(r1);
        BinStrTree r3;
        r3 = r1;
        r3 = r3;

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
