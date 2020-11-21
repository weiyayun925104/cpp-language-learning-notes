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

template<typename L, typename R, typename O>
O max(const L& left, const R& right)
{
  return left > right ? left : right;
}

int main()
{
  cout << max<int, double, double>(5, 6.5) << endl;
  cout << max<int, double, int>(5, 6.5) << endl;
  return 0;
}
