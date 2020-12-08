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
#include <cmath>

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
using std::to_string;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

vector<int> primes_norm;

bool is_prime(int n)
{
    for (int i = 0; i < primes_norm.size() && primes_norm[i] <= sqrt(n); ++i)
    {
        if (n % primes_norm[i] == 0)
        {
            return false;
        }
    }
    return true;
}

void init_prime(int n)
{
    if (n < 100)
    {
        return ;
    }
    primes_norm.clear();
    int i, j;
    char *buffer = new char[n + 1];
    for(i = 1; i <= n; i++)
    {
        buffer[i] = 0;
    }
    for(i = 2; i <= n; i++)
    {
        if(buffer[i] == 0)
        {
            primes_norm.push_back(i);
        }
        if( i <= ( (n / 2) + 1) )
        {
            for(j = 0; j < primes_norm.size() && primes_norm[j] * i <= n; j++)
            {
                buffer[primes_norm[j]*i] = 1;
                if(i % primes_norm[j] == 0)
                {
                    break;
                }
            }
        }
    }
    delete [] buffer;
}

int main()
{
    init_prime(100);
    for (int i = 0; i < primes_norm.size(); ++i)
    {
        cout << primes_norm[i] << endl;
    }
}
