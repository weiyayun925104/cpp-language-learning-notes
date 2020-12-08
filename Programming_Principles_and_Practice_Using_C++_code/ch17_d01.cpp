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

void print_array(ostream &os, int *a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        os << a[i] << "\n";
    }
}

void print_vector(ostream &os, const vector<int> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i] << "\n";
    }
}

int main()
{
    try
    {
        int *ip = new int[10];

        cout << "*** 2 ***\n";
        for (int i = 0; i < 10; ++i)
        {
            cout << ip[i] << "\n";
        }

        delete[] ip;

        cout << "*** 5 ***\n";
        int *ip2 = new int[10];

        for (int i = 0; i < 10; ++i)
        {
            ip2[i] = 100 + i;
        }
        print_array(cout, ip2, 10);

        delete[] ip2;

        cout << "*** 6 ***\n";
        int *ip3 = new int[11];

        for (int i = 0; i < 11; ++i)
        {
            ip3[i] = 100 + i;
        }
        print_array(cout, ip3, 11);

        delete[] ip3;

        cout << "*** 8 ***\n";
        int *ip4 = new int[20];

        for (int i = 0; i < 20; ++i)
        {
            ip4[i] = 100 + i;
        }
        print_array(cout, ip4, 20);

        delete[] ip4;

        cout << "*** 10 ***\n";
        vector<int> v;
        for (int i = 0; i < 10; ++i)
        {
            v.push_back(100 + i);
        }
        print_vector(cout, v);

        cout << "\n";
        vector<int> v2;
        for (int i = 0; i < 11; ++i)
        {
            v2.push_back(100 + i);
        }
        print_vector(cout, v2);

        cout << "\n";
        vector<int> v3;
        for (int i = 0; i < 20; ++i)
        {
            v3.push_back(100 + i);
        }
        print_vector(cout, v3);


        int i1 = 7;
        int *p1 = &i1;

        cout << "*** 2 ***\n";
        cout << "p1: " << p1 << "\n";
        cout << "*p1: " << *p1 << "\n";

        int *p2 = new int[7];
        for (int i = 0; i < 7; ++i)
        {
            p2[i] = pow(2, i);
        }

        cout << "*** 4 ***\n";
        cout << "p2: " << p2 << "\n";
        cout << "print_array(cout, p2, 7):\n";
        print_array(cout, p2, 7);

        int *p3 = p2;

        p2 = p1;

        p2 = p3;

        cout << "*** 8 ***\n";
        cout << "p1: " << p1 << "\n";
        cout << "*p1: " << *p1 << "\n";
        cout << "p2: " << p2 << "\n";
        cout << "*p2: " << *p2 << "\n";

        delete[] p2;
        p3 = nullptr;

        p1 = new int[10];
        for (int i = 0; i < 10; ++i)
        {
            p1[i] = pow(2, i);
         }

        p2 = new int[10];

        cout << "*** 12 ***\n";
        for (int i = 0; i < 10; ++i)
        {
            p2[i] = p1[i];
        }
        print_array(cout, p2, 10);

       delete [] p1;
       delete [] p2;

        cout << "*** 13 ***\n";
        vector<int> vec1;
        for (int i = 0; i < 10; ++i)
        {
            vec1.push_back(pow(2, i));
        }
        vector<int> vec2;
        for (int i = 0; i < vec1.size(); ++i)
        {
            vec2.push_back(vec1[i]);
        }
        print_vector(cout, vec2);
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
