#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <utility>
#include <chrono>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::stringstream;
using std::vector;
using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::list;
using std::getline;
using std::find_if;
using std::search;
using std::copy;
using std::sort;
using std::transform;
using std::accumulate;
using std::inserter;
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;
using std::logic_error;
using std::domain_error;
using std::to_string;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

template<typename In, typename T>
bool binarySearch(In b, In e, const T &x)
{
    while (b < e)
    {
        In mid = b + (e - b) / 2;
        if (x < *mid)
        {
            e = mid;
        }
        else if (*mid < x)
        {
            b = mid + 1;
        }
        else
        {
            return true;
        }
    }
    return false;
}

int main()
{
    vector<int> v = { 4, 17, 9, 23, 36 };

    cout << binarySearch<vector<int>::iterator,int>(v.begin(), v.end(), 23) << endl;
    cout << binarySearch<vector<int>::iterator,int>(v.begin(), v.end(), 35) << endl;

    return 0;
}
