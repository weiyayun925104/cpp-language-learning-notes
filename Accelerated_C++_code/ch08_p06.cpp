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


int main()
{
    map<int, string> m1 = { { 1, "hello" }, { 3, "bye" } };
    vector<pair<int, string>> v1;

    cout << v1.size() << endl;
    copy(m1.begin(), m1.end(), back_inserter(v1));
    cout << v1.size() << endl;

    map<int, string> m2;
    vector<pair<int, string>> v2 = { { 1, "thanks" }, { 3, "yo" } };

    cout << m2.size() << endl;
    copy(v2.begin(), v2.end(), inserter(m2, m2.begin()));
    cout << m2.size() << endl;

    return 0;
}
