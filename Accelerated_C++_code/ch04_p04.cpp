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

vector<double> square_double(unsigned int range)
{
    vector<double> squares;
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

double GetNumberOfDigits(double i)
{
    return i > 0 ? log10(i) + 1 : 1;
}

ostream &print_squares(ostream &os, const vector<double> &v)
{
    if (os)
    {
        streamsize digits_i = (streamsize) GetNumberOfDigits(v.size());
        streamsize digits_v = (streamsize) GetNumberOfDigits(v.back());

        streamsize s_size = os.width();
        for (vector<double>::size_type i = 0; i < v.size(); i++)
        {
            os << setw(digits_i + 1) << i << " " << setw(digits_v + 1) << v[i] << endl;
        }
        os.width(s_size);
    }

    return os;
}

int main()
{
    vector<double> v = square_double(500);
    print_squares(cout, v);

    return 0;
}
