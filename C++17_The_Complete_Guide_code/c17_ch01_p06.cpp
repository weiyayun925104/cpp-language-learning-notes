#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <bitset>
#include <regex>
#include <stack>
#include <queue>
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
#include <limits>
#include <type_traits>
#include <initializer_list>
#include <functional>
#include <streambuf>
#include <locale>
#include <codecvt>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
#include <boost/type_index.hpp>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cwctype>
#include <climits>
#include <ctime>
#include <cmath>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::istream_iterator;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::replace_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::streampos;
using std::streambuf;
using std::setprecision;
using std::setw;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;
using std::ios_base;
using std::ios;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::right;
using std::flush;
using std::numeric_limits;
using std::common_type;
using std::reverse;
using std::begin;
using std::end;
using std::initializer_list;
using std::function;
using std::bind;
using std::out_of_range;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::uninitialized_copy_n;
using std::uninitialized_fill_n;
using std::make_shared;
using std::make_unique;
using std::tuple;
using std::make_tuple;
using std::tuple_size;
using std::tuple_element;
using std::bitset;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::regex_replace;
using std::smatch;
using std::ssub_match;
using std::sregex_iterator;
using std::locale;

template<typename T>
void f(T &&x)
{
    using boost::typeindex::type_id_with_cvr;
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n';
    std::cout << "x = " << type_id_with_cvr<decltype(x)>().pretty_name() << '\n';
}

int main(int argc, const char *argv[])
{
    try
    {
        int &&d = 1;
        f(d);
        f(1);

        using boost::typeindex::type_id_with_cvr;

        int array[2] { 1, 2 };
        auto &[i, j] = array;
        std::cout << "i = " << type_id_with_cvr<decltype(i)>().pretty_name() << '\n';
        std::cout << "j = " << type_id_with_cvr<decltype(j)>().pretty_name() << '\n';

        const auto &[i2, j2] = array;
        std::cout << "i2 = " << type_id_with_cvr<decltype(i2)>().pretty_name() << '\n';
        std::cout << "j2 = " << type_id_with_cvr<decltype(j2)>().pretty_name() << '\n';

        std::pair pair{ 1, 2.0 };
        int number = 3;
        std::tuple<int &> tuple(number);
        const auto& [ival, fval] = pair;
        const auto& [rival] = tuple;
        std::cout << "ival = " << type_id_with_cvr<decltype(ival)>().pretty_name() << '\n';
        std::cout << "fval = " << type_id_with_cvr<decltype(fval)>().pretty_name() << '\n';
        std::cout << "rival = " << type_id_with_cvr<decltype(rival)>().pretty_name() << '\n';

        auto& [ival2, fval2] = pair;
        auto& [rival2] = tuple;
        std::cout << "ival2 = " << type_id_with_cvr<decltype(ival2)>().pretty_name() << '\n';
        std::cout << "fval2 = " << type_id_with_cvr<decltype(fval2)>().pretty_name() << '\n';
        std::cout << "rival2 = " << type_id_with_cvr<decltype(rival2)>().pretty_name() << '\n';

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
