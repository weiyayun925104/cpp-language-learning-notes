#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>

using std::ostream;
using std::streamsize;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::domain_error;
using std::setw;

vector<int> square(unsigned int range)
{
    vector<int> squares;
    if (range > squares.max_size())
    {
        throw domain_error("Range argument exceeds vector limit.");
    }

    for (unsigned int i = 0; i < range; i++)
    {
        squares.push_back(i * i);
    }

    return squares;
}

unsigned GetNumberOfDigits(unsigned i)
{
    return i > 0 ? (int)log10((double)i) + 1 : 1;
}

ostream &print_squares_robust(ostream &os, const vector<int> &v)
{
    if (os)
    {
        unsigned digits_i = GetNumberOfDigits(v.size());
        unsigned digits_v = GetNumberOfDigits(v.back());
        streamsize s_size = os.width();
        for (vector<int>::size_type i = 0; i < v.size(); i++)
        {
            os << setw(digits_i + 1) << i << " " << setw(digits_v + 1) << v[i] << endl;
        }
        os.width(s_size);
    }

    return os;
}

int main()
{
    vector<int> v = square(1000);
    print_squares_robust(cout, v);

    return 0;
}
