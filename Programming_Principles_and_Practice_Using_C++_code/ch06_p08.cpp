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

vector<char> get_new_solution(mt19937 &e)
{
    vector<char> solution(4);
    solution[0] = 'a' + nrand_improved(26, e);
    solution[1] = 'a' + nrand_improved(26, e);
    solution[2] = 'a' + nrand_improved(26, e);
    solution[3] = 'a' + nrand_improved(26, e);
    return solution;
}

void check_guess(const vector<char> &guess, const vector<char> &solution)
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
        char c0 = 0;
        char c1 = 0;
        char c2 = 0;
        char c3 = 0;
        vector<char> guess(4);
        cout << "Guess four character!\n";
        vector<char> solution = get_new_solution(engine);
        print_vector(solution, cout);

        cout << "Enter your guess:\n";
        while (cin >> c0 && cin >> c1 && cin >> c2 && cin >> c3)
        {
            while (cin.get() != '\n') { continue; }
            guess[0] = c0;
            guess[1] = c1;
            guess[2] = c2;
            guess[3] = c3;

            check_guess(guess, solution);
            if (bulls == 4)
            {
                cout << "You have guessed the four character! Setting new solution...\n";
                solution = get_new_solution(engine);
                print_vector(solution, cout);
            }
            if (bulls < 4)
            {
                cout << "Number of bulls: " << bulls << endl;
                cout << "Number of cows: " << cows << endl;
            }
            cout << "Enter your guess:\n";
        }
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
