#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::stringstream;
using std::vector;
using std::string;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
using std::accumulate;
using std::find;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;


template <typename In>
string print_vector(In b, In e)
{
    if (b == e)
    {
        throw domain_error("Empty range");
    }

    stringstream ss;

    ss << "[ " << *b++;

    while (b != e)
    {
        ss << ", " << *b++;
    }

    ss << " ]";

    return ss.str();
}

template <typename T>
string print_vector(const vector<T> &vec)
{
    return print_vector(vec.begin(), vec.end());
}

template<typename In>
auto median_iter(In b, In e) -> decltype((*b + *b) / 2)
{
    auto count = std::distance(b, e);

    if (count == 0)
    {
        throw std::domain_error("median of empty container");
    }

    std::sort(b, e);

    auto mid = count / 2;

    std::advance(b, mid - 1);

    return count % 2 == 0 ? (*b++ + *b) / 2 : *++b;
}

template<typename T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }
    std::sort(v.begin(), v.end());

    vec_sz mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

int main()
{
    vector<int> vec1 = { 85, 74, 75, 45, 49, 66};
    cout << print_vector(vec1) << endl;
    steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; i++)
    {
        cout << median(vec1) << endl;
    }

    steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Microseconds to run median 100 times using pass by value = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
    cout << print_vector(vec1) << endl;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
    {
        cout << median_iter<vector<int>::iterator>(vec1.begin(), vec1.end()) << endl;
    }

    end = std::chrono::steady_clock::now();
    cout << "Microseconds to run median 100 times using iterators = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
    cout << print_vector(vec1) << endl;
    return 0;
}
