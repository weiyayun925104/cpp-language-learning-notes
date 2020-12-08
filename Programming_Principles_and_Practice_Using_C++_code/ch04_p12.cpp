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

int getPrimeFactor(int n)
{
    if (n <= 1)
    {
        return 0;
    }

    for (int i = 0; i < primes_norm.size() && primes_norm[i] <= sqrt(n); ++i)
    {
        if (n % primes_norm[i] == 0)
        {
            return primes_norm[i];
        }
    }

    return 0;
}

string numberHasPrimeFactorsWhichSumToPrime(int n)
{
    if (n <= 1)
    {
        return "";
    }
    if (is_prime(n))
    {
        return to_string(n) + " is prime number.\n";
    }

    int remainder = n;
    int currentSum = 0;
    string message = to_string(n) + " has prime factors: ";
    bool isFirstTerm = true;
    while (true)
    {
        int primeFactor = getPrimeFactor(remainder);
        if (primeFactor == 0)
        {
            return "An error has occurred with number " + to_string(n) + "\n";
        }
        if (!isFirstTerm)
        {
            message += ", ";
        }
        message += to_string(primeFactor);

        currentSum += primeFactor;
        remainder = (remainder / primeFactor);

        if (is_prime(remainder))
        {
            if (is_prime(remainder + currentSum))
            {
                message += ", " + to_string(remainder);
                message += " Which sum to: " + to_string(remainder + currentSum) + "\n";
                return message;
            }
            return "";
        }
        isFirstTerm = false;
    }
    return "";
}

int main()
{
    int n_primes = 200;
    primes_norm.push_back(2);
    int i = 3;
    while (primes_norm.size() < n_primes)
    {
        if (is_prime(i))
        {
            primes_norm.push_back(i);
        }
        i += 2;
    }

    for (int i = 1; i <= 1000; i++)
    {
        string message = numberHasPrimeFactorsWhichSumToPrime(i);
        if (!(message == ""))
        {
            cout << message;
        }
    }
}
