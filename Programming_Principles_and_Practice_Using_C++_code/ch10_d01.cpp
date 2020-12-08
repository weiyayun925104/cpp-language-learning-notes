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
using std::swap;
using std::stable_partition;
using std::streamsize;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
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

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) { }
    Point(int xx, int yy) : x(xx), y(yy) { }
};

bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point &p1, const Point &p2)
{
    return !(p1 == p2);
}

ostream &operator<<(ostream &os, const Point &p)
{
    return os << '(' << p.x << ',' << p.y << ')';
}

istream &operator>>(istream &is, Point &p)
{
    int x, y;
    char ch1, ch2, ch3;
    is >> ch1 >> x >> ch2 >> y >> ch3;
    if (!is)
    {
        return is;
    }
    if (ch1 != '(' || ch2 != ',' || ch3 != ')')
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    p = Point(x, y);
    return is;
}

void print_vector(const vector<Point> &points)
{
    for (int i = 0; i < points.size(); ++i)
    {
        cout << points[i] << endl;
    }
}

void write_to_file(const vector<Point> &points, const string &name)
{
    ofstream ost(name.c_str());
    if (!ost)
    {
        error("can't open output file " + name);
    }
    for (int i = 0; i < points.size(); ++i)
    {
        ost << points[i] << endl;
    }
}

void fill_from_file(vector<Point> &points, const string &name)
{
    ifstream ist(name.c_str());
    if (!ist)
    {
        error("can't open input file " + name);
    }
    Point pp;
    while (ist >> pp)
    {
        points.push_back(pp);
    }
}

bool compare_vectors(const vector<Point> &points1, const vector<Point> &points2)
{
    if (points1.size() != points2.size())
    {
        cerr << "compare_vectors: points1.size() != points2.size()" << endl;
        return false;
    }
    for (int i = 0; i < points1.size(); ++i)
    {
        if (points1[i] != points2[i])
        {
            cerr << "compare_vectors: points1[i] != points2[i]" << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    try
    {
        vector<Point> original_points;
        cout << "Enter 7 (x,y) pairs:\n";
        for (int i = 0; i < 7; ++i)
        {
            Point p;
            cin >> p;
            original_points.push_back(p);
        }

        cout << "\nOriginal points:\n";
        print_vector(original_points);

        string filename = "ch10_d01.txt";
        write_to_file(original_points, filename);

        vector<Point> processed_points;
        fill_from_file(processed_points, filename);

        cout << "\nData from ifstream:\n";
        print_vector(processed_points);
        cout << "\nOriginal data:\n";
        print_vector(original_points);

        if ( compare_vectors(original_points, processed_points) )
        {
            cout << "original_points == processed_points" << endl;
        }
        else
        {
            cout << "original_points != processed_points" << endl;
        }
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
