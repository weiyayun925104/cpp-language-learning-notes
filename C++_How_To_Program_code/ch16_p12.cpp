#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
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
#include <limits>
#include <type_traits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include<climits>
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
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::vector;
using std::list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::stoi;
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
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::streampos;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
}

template<typename T>
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

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}

int arrayMaxLength = 8;

struct Talk
{
    string name;
    string daysSinceLastSpoken;
};

string getName()
{
    string name;
    cout << "Friend name: ";
    getline(cin, name, '\n');
    cout << '\n';
    return name;
}
int getDaysSinceLastSpoken()
{
    int daysSinceLastSpokenInput = 0;
    do
    {
        cout << "Number of days ago you last spoke with them: ";
        cin >> daysSinceLastSpokenInput;
        cin.clear();
        cin.ignore(80, '\n');

        if (daysSinceLastSpokenInput < 0)
        {
            cout << "Please enter a value >= 0\n";
        }
    }
    while (daysSinceLastSpokenInput < 0);
    cout << '\n';
    return daysSinceLastSpokenInput;
}
int getDaysSinceLastSpoken(int lastDaysSinceLastSpoken)
{
    int daysSinceLastSpokenInput = 0;
    do
    {
        cout << "Number of days ago you last spoke with them: ";
        cin >> daysSinceLastSpokenInput;
        cin.clear();
        cin.ignore(80, '\n');

        if (daysSinceLastSpokenInput < 0)
        {
            cout << "Please enter a value >= 0\n\n";
        }
        if (daysSinceLastSpokenInput > lastDaysSinceLastSpoken)
        {
            cout << "You last spoke with your friend " << lastDaysSinceLastSpoken << " days ago.\n";
            cout << "You must enter a number less than or equal to this.\n\n";
        }
    }
    while ((daysSinceLastSpokenInput < 0) || (daysSinceLastSpokenInput > lastDaysSinceLastSpoken));
    cout << '\n';
    return daysSinceLastSpokenInput;
}
int lookUpDaysSinceLastSpoken(Talk *p_array, int size, string name)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            return stoi( p_array[i].daysSinceLastSpoken );
        }
    }
    return -1;
}

int findSmallestElementByName(Talk *p_array, int size, int index)
{
    int indexOfSmallestValue = index;
    for (int i = index + 1; i < size; i++)
    {
        if ( p_array[i].name < p_array[indexOfSmallestValue].name )
        {
            indexOfSmallestValue = i;
        }
    }
    return indexOfSmallestValue;
}

int findSmallestElementByDate(Talk *p_array, int size, int index)
{
    int indexOfSmallestValue = index;
    for (int i = index + 1; i < size; i++)
    {
        int arrayCurrent = stoi( p_array[i].daysSinceLastSpoken );
        int arraySmallest = stoi( p_array[indexOfSmallestValue].daysSinceLastSpoken );
        if (arrayCurrent < arraySmallest)
        {
            indexOfSmallestValue = i;
        }
    }
    return indexOfSmallestValue;
}

void swap(Talk *p_array, int firstIndex, int secondIndex)
{
    if (firstIndex == secondIndex)
    {
        return;
    }
    Talk temp = p_array[firstIndex];
    p_array[firstIndex] = p_array[secondIndex];
    p_array[secondIndex] = temp;
}

void sortByName(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int index = findSmallestElementByName(p_array, size, i);
        swap(p_array, i, index);
    }
}
void sortByDate(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int index = findSmallestElementByDate(p_array, size, i);
        swap(p_array, i, index);
    }
}

Talk *arraySortedByName(Talk *p_array, int size)
{
    Talk *p_newArray = new Talk[size];
    for (int i = 0; i < size; i++)
    {
        p_newArray[i] = p_array[i];
    }
    sortByName(p_newArray, size);

    return p_newArray;
}

Talk *arraySortedByDate(Talk *p_array, int size)
{
    Talk *p_newArray = new Talk[size];
    for (int i = 0; i < size; i++)
    {
        p_newArray[i] = p_array[i];
    }
    sortByDate(p_newArray, size);

    return p_newArray;
}

bool nameExistsInArray(Talk *p_array, int size, string name)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            return true;
        }
    }
    return false;
}

void disposeArray(Talk *p_array)
{
    delete[] p_array;
}

void printFriends(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << p_array[i].name << ": " << p_array[i].daysSinceLastSpoken << " days since last spoken\n";
    }
}

void printFriendsByName(Talk *p_array, int size)
{
    Talk *sortedArray = arraySortedByName(p_array, size);
    printFriends(sortedArray, size);
    disposeArray(sortedArray);
}
void printFriendsByDate(Talk *p_array, int size)
{
    Talk *sortedArray = arraySortedByDate(p_array, size);
    printFriends(sortedArray, size);
    disposeArray(sortedArray);
}

string getNameToUpdate(Talk *p_array, int size)
{
    string name;
    do
    {
        printFriendsByName(p_array, size);
        cout << '\n';
        cout << "Please enter an existing name to update: ";
        getline(cin, name, '\n');
        cout << '\n';
    }
    while (!nameExistsInArray(p_array, size, name));
    return name;
}

void updateArray(Talk *p_array, int size, string name, int daySinceLastSpoken)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            p_array[i].daysSinceLastSpoken = to_string(daySinceLastSpoken);
            return;
        }
    }
}
Talk *addToArray(Talk *p_array, int *size, string name, int daySinceLastSpoken)
{
    if (*size >= arrayMaxLength)
    {
        Talk *p_newvalues = new Talk[ arrayMaxLength * 2 ];
        for (int j = 0; j < arrayMaxLength; j++)
        {
            p_newvalues[j] = p_array[j];
        }
        p_newvalues[arrayMaxLength].name = name;
        p_newvalues[arrayMaxLength].daysSinceLastSpoken = to_string(daySinceLastSpoken);
        disposeArray(p_array);
        *size += 1;
        arrayMaxLength *= 2;
        return p_newvalues;
    }
    else
    {
        p_array[*size].name = name;
        p_array[*size].daysSinceLastSpoken = to_string(daySinceLastSpoken);
        *size += 1;
        return p_array;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        int arrayLength = 0;
        Talk *p_array = new Talk[ arrayMaxLength ];

        int option = 0;
        string name;
        int daysSinceLastSpoken;
        do
        {
            cout << "Please select an option:\n";
            cout << "(1) Add new friend\n";
            if(arrayLength > 0)
            {
                cout << "(2) Update friend\n";
                cout << "(3) List friends by name\n";
                cout << "(4) List friends by most recently spoken with\n";
            }
            cout << "(0) Exit\n";
            cin >> option;
            cin.clear();
            cin.ignore(80, '\n');

            cout << '\n';
            switch (option)
            {
            case 1:
                name = getName();
                daysSinceLastSpoken = getDaysSinceLastSpoken();
                p_array = addToArray(p_array, &arrayLength, name, daysSinceLastSpoken);
                cout << '\n';
                break;
            case 2:
                name = getNameToUpdate(p_array, arrayLength);
                daysSinceLastSpoken = lookUpDaysSinceLastSpoken(p_array, arrayLength, name);
                daysSinceLastSpoken = getDaysSinceLastSpoken(daysSinceLastSpoken);
                updateArray(p_array, arrayLength, name, daysSinceLastSpoken);
                cout << '\n';
                break;
            case 3:
                printFriendsByName(p_array, arrayLength);
                cout << '\n';
                break;
            case 4:
                printFriendsByDate(p_array, arrayLength);
                cout << '\n';
                break;
            case 0:
                break;
            default:
                break;
            }
        }
        while (option != 0);

        disposeArray(p_array);

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
