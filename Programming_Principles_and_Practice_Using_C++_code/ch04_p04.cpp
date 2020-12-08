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

int main()
{
    cout << "Think of a number between 1 and 100.\n";
    cout << "For every guess, enter if your number is\n";
    cout << "(l)arger or (s)maller than the one shown.\n";
    cout << "Enter 'c' (for 'correct') if the number shown is yours.\n";

    int guess = 50;
    vector<int> differences(6);
    differences[0] = 25;
    differences[1] = 13;
    differences[2] = 6;
    differences[3] = 3;
    differences[4] = 2;
    differences[5] = 1;
    int counter = 0;
    char answer = ' ';

    while (answer != 'c')
    {
        cout << "My guess: " << guess << endl;
        ++counter;
        cout << "Correct, larger or smaller (c, l, s)? ";
        cin >> answer;
        switch (answer)
        {
        case 'c':
            break;
        case 'l':
            if (counter <= differences.size())
            {
                guess += differences[counter - 1];
            }
            else
            {
                ++guess;
            }
            break;
        case 's':
            if (counter <= differences.size())
            {
                guess -= differences[counter - 1];
            }
            else
            {
                --guess;
            }
            break;
        default:
            cout << "This is not a valid answer, use 'c', 'l' or 's'\n";
            --counter;
            break;
        }
        if (guess > 100 || guess < 1)
        {
            cout << "Your number must be between 1 and 100!\n";
            return 0;
        }
        if (counter == 7 && answer != 'c')
        {
            cout << "Super fishy, dude. I should have your number by now.\n";
            return 0;
        }
    }

    string s_try;
    if (counter == 1)
    {
        s_try = " try ";
    }
    else
    {
        s_try = " tries ";
    }
    cout << "It took me " << counter << s_try << "to find your number, " << guess << ".\n";
}
