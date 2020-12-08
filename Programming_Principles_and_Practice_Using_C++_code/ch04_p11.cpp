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
    for (int i = 0; i < primes_norm.size() && primes_norm[i]<=sqrt(n); ++i)
    {
        if (n % primes_norm[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "How many primes should I find?\n";
    int n_primes = 0;
    cin >> n_primes;
    primes_norm.push_back(2);
    int i = 3;
    while (primes_norm.size() < n_primes)
    {
        if (is_prime(i))
        {
            primes_norm.push_back(i);
        }
        i+=2;
    }

    cout << endl;

    for (int i = 0; i < primes_norm.size(); ++i)
    {
        cout << primes_norm[i] << endl;
    }
}
