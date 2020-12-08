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
    vector<double> distances;
    double distance;
    double total = 0;
    double smallest = 0;
    double greatest = 0;
    double mean = 0;
    while (cin >> distance)
    {
        if (distance > 0)
        {
            distances.push_back(distance);
        }
    }
    if (distances.size() == 0)
    {
        error("No valid values entered");
    }
    smallest = distances[0];
    greatest = distances[0];
    for (int i = 0; i < distances.size(); ++i)
    {
        total += distances[i];
        if (distances[i] < smallest)
        {
            smallest = distances[i];
        }
        if (distances[i] > greatest)
        {
            greatest = distances[i];
        }
    }
    mean = total / distances.size();
    cout << "Total distance: " << total << endl;
    cout << "Smallest distance: " << smallest << endl;
    cout << "Greatest distance: " << greatest << endl;
    cout << "Mean distance: " << mean << endl;
    return 0;
}
