#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <cstring>

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
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::max;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;

int pointers()
{
    int x = 5;

    int *p = &x;
    cout << "x = " << x << endl;

    *p = 6;
    cout << "x = " << x << endl;
    return 0;
}

string letter_grade(double grade)
{
    static const double numbers[] =
    {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };
    static const char *const letters[] =
    {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);
    for (size_t i = 0; i < ngrades; ++i)
    {
        if (grade >= numbers[i])
        {
            return letters[i];
        }
    }
    return "?\?\?";
}

int copy_file(string in, string out)
{
    ifstream infile(in);
    ofstream outfile(out);
    string s;
    while (getline(infile, s, '\n'))
    {
        outfile << s << endl;
    }
    return 0;
}

int print_files(int argc, const char * argv[])
{
    int fail_count = 0;
    for (int i = 0; i < argc; ++i)
    {
        ifstream in(argv[i]);
        if (in)
        {
            string s;
            while (getline(in, s, '\n'))
            {
                cout << s << endl;
            }
        }
        else
        {
            cerr << "cannot open file " << argv[i] << endl;
            ++fail_count;
        }
    }
    return fail_count;
}

char *duplicate_chars(const char *p)
{
    size_t length = strlen(p) + 1;
    char *result = new char[length];
    copy(p, p + length, result);
    return result;
}

int main()
{
    pointers();
    cout << letter_grade(75.0) << endl;
    copy_file("in_ch10.txt", "out_ch10.txt");
    const char *files[] = { "in_ch10.txt", "out_ch10.txt" };
    print_files(2, files);
    char *str = duplicate_chars("test");
    cout << str << endl;
    return 0;
}
