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
    vector<string> words;
    string temp;
    while (cin >> temp)
    {
        words.push_back(temp);
    }
    vector<string> dislikeds;
    dislikeds.push_back("Broccoli");
    dislikeds.push_back("Chewbacca");
    dislikeds.push_back("Eggplant");
    for (int i = 0; i < words.size(); ++i)
    {
        bool is_disliked = false;
        for (int j = 0; j < dislikeds.size(); ++j)
        {
            if (dislikeds[j] == words[i])
            {
                is_disliked = true;
            }
        }
        if (is_disliked)
        {
            cout << "BLEEP ";
        }
        else
        {
            cout << words[i] << ' ';
        }
    }
    cout << endl;
    return 0;
}
