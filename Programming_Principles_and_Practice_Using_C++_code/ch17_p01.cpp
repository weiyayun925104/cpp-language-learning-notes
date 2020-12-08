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
#include <utility>
#include <random>
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
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

long ptr_to_long(void *ptr)
{
    ostringstream oss;
    oss << ptr;
    istringstream iss(oss.str());
    long address;
    iss >> hex >> address;
    if (!iss) { error("problem reading address"); }
    return address;
}

struct X
{
    int a, b, c;
};

struct V
{
    int a, b, c;
    virtual void f() { }
};

int main()
{
    try
    {
        cout << "Output format of a pointer:\n";
        int *pi = new int(0);
        cout << "pi = " << pi << "\n";
        cout << "*pi = " << *pi << "\n";
        cout << "&pi[1] = " << &pi[1] << "\n";
        delete pi;

        cout << "\nNumber of bytes of different types:\n";
        pi = new int[2];
        pi[0] = 0;
        pi[1] = 0;
        int var_size = ptr_to_long(&pi[1]) - ptr_to_long(pi);
        cout << "int: " << &pi[1] << " - " << pi << " = " << var_size << " bytes.\n";
        cout << "sizeof(int): " << sizeof(int) << "\n";
        delete[] pi;

        char *pc = new char[2];
        pc[0] = 0;
        pc[1] = 0;
        var_size = ptr_to_long(&pc[1]) - ptr_to_long(pc);
        cout << "char: " << (void *)&pc[1] << " - " << (void *)pc << " = " << var_size << " bytes.\n";
        cout << "sizeof(char): " << sizeof(char) << "\n";
        delete[] pc;

        double *pd = new double[2];
        pd[0] = 0;
        pd[1] = 0;
        var_size = ptr_to_long(&pd[1]) - ptr_to_long(pd);
        cout << "double: " << &pd[1] << " - " << pd << " = " << var_size << " bytes.\n";
        cout << "sizeof(double): " << sizeof(double) << "\n";
        delete[] pd;

        bool *pb = new bool[2];
        pb[0] = 0;
        pb[1] = 0;
        var_size = ptr_to_long(&pb[1]) - ptr_to_long(pb);
        cout << "bool: " << &pb[1] << " - " << pb << " = " << var_size << " bytes.\n";
        cout << "sizeof(bool): " << sizeof(bool) << "\n";
        delete[] pb;

        X *pX = new X[2];
        var_size = ptr_to_long(&pX[1]) - ptr_to_long(pX);
        cout << "struct X: " << &pX[1] << " - " << pX << " = " << var_size << " bytes.\n";
        cout << "sizeof(X): " << sizeof(X) << "\n";

        V *pV = new V[2];
        var_size = ptr_to_long(&pV[1]) - ptr_to_long(pV);
        cout << "struct V: " << &pV[1] << " - " << pV << " = " << var_size << " bytes.\n";
        cout << "sizeof(V): " << sizeof(V) << "\n";
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
