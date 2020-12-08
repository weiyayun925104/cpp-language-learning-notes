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
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_improved(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

template<class T>
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

int bulls = 0;
int cows = 0;

vector<int> get_new_solution(mt19937 &e)
{
    vector<int> solution(4);
    solution[0] = nrand_improved(10, e);
    solution[1] = nrand_improved(10, e);
    solution[2] = nrand_improved(10, e);
    solution[3] = nrand_improved(10, e);
    return solution;
}

vector<int> int_to_vector(int n)
{
    if (n > 9999 || n < 0)
    {
        error("int_to_vector called with wrong number");
    }
    vector<int> v(4);
    v[0] = n / 1000 % 10;
    v[1] = n / 100 % 10;
    v[2] = n / 10 % 10;
    v[3] = n % 10;
    return v;
}

void check_guess(const vector<int> &guess, const vector<int> &solution)
{
    bulls = 0;
    cows = 0;
    vector<char> is_bull(4, 'n');
    vector<char> is_cow(4, 'n');
    for (int i = 0; i < solution.size(); ++i)
    {
        if (guess[i] == solution[i])
        {
            ++bulls;
            is_bull[i] = 'y';
        }
    }
    for (int i = 0; i < solution.size(); ++i)
    {
        if (is_bull[i] == 'n')
        {
            for (int j = 0; j < guess.size(); ++j)
            {
                if (is_bull[j] == 'n' && is_cow[j] == 'n')
                {
                    if (solution[i] == guess[j])
                    {
                        ++cows;
                        is_cow[j] = 'y';
                    }
                }
            }
        }
    }
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 engine(seed);

    try
    {
        int guess = 0;
        cout << "Guess my four digit number! Numbers with less digits will be padded with zeros.\n";
        vector<int> solution = get_new_solution(engine);
        print_vector(solution, cout);
        cout << "Enter guess ('q' to exit): ";
        while (cin >> guess)
        {
            if (guess > 9999 || guess < 0)
            {
                cout << "Number must be between 0000 and 9999!\n";
            }
            else
            {
                vector<int> v_guess = int_to_vector(guess);
                check_guess(v_guess, solution);
                if (bulls == 4)
                {
                    cout << "You have guessed the number! Setting new solution...\n";
                    solution = get_new_solution(engine);
                    print_vector(solution, cout);
                }
                if (bulls < 4)
                {
                    cout << "Number of bulls: " << bulls << endl;
                    cout << "Number of cows: " << cows << endl;
                }
            }
            cout << "Enter guess ('q' to exit): ";
        }
        cout << "You gave up!\n";
        return 0;
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception!\n";
        return 2;
    }
}
