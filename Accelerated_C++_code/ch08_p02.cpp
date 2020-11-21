#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::stringstream;
using std::vector;
using std::string;
using std::domain_error;
using std::back_inserter;
using std::streamsize;
using std::setprecision;

class algorithms
{
public:
    template <typename In1, typename In2>
    static bool equal(In1 b, In1 e, In2 d)
    {
        while (b != e)
        {
            if (*b++ != *d++)
            {
                return false;
            }
        }

        return true;
    }

    template <typename Fw1, typename Fw2>
    static Fw1 search(Fw1 b, Fw1 e, Fw2 b2, Fw2 e2)
    {
        while (b != e)
        {
            Fw1 b_pat = b;
            Fw2 b2_pat = b2;

            while (*b_pat++ == *b2_pat++)
            {
                if (b2_pat == e2)
                {
                    return b;
                }
                if (b_pat == e)
                {
                    return e;
                }
            }

            ++b;
        }

        return e;
    }

    template <typename In, typename X>
    static In find(In b, In e, const X &t)
    {
        while (b != e && *b != t)
        {
            ++b;
        }

        return b;
    }

    template <typename In, typename P>
    static In find_if(In b, In e, P p)
    {
        while (b != e && !p(*b))
        {
            ++b;
        }

        return b;
    }

    template <typename In, typename Out>
    static Out copy(In b, In e, Out d)
    {
        while (b != e)
        {
            *d++ = *b++;
        }

        return d;
    }

    template <typename In, typename Out, typename X>
    static Out remove_copy(In b, In e, Out d, const X &t)
    {
        while (b != e)
        {
            if (*b != t)
            {
                *d++ = *b;
            }
            ++b;
        }

        return d;
    }

    template <typename In, typename Out, typename P>
    static Out remove_copy_if(In b, In e, Out d, P p)
    {
        while (b != e)
        {
            if (!p(*b))
            {
                *d++ = *b;
            }
            ++b;
        }

        return d;
    }

    template <typename Fw, typename X>
    static Fw remove(Fw b, Fw e, const X &t)
    {
        Fw b_in = b;

        while (b_in != e)
        {
            if (*b_in != t)
            {
                *b++ = *b_in;
            }

            ++b_in;
        }

        return b;
    }

    template <typename In, typename Out, typename P>
    static Out transform(In b, In e, Out d, P p)
    {
        while (b != e)
        {
            *d++ = p(*b++);
        }

        return d;
    }

    template <typename Fw, typename P>
    static Fw partition(Fw b, Fw e, P p)
    {
        Fw b_out = b;

        while (b != e)
        {
            if (p(*b))
            {
                std::iter_swap(b, b_out++);
            }
            b++;
        }

        return b_out;
    }

    template <typename In, typename X>
    static X accumulate(In b, In e, X t)
    {
        while (b != e)
        {
            t += *b++;
        }

        return t;
    }

};

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

template <typename X>
string print_vector(const vector<X> &vec)
{
    return print_vector(vec.begin(), vec.end());
}

bool is_40(int x)
{
    return x == 40;
}

int minus_5(int x)
{
    return x - 5;
}

bool divisible_10(int x)
{
    return x % 10 == 0;
}

int main()
{
    vector<int> vec1 = { 10, 25, 35, 40, 50 };
    vector<int> vec2 = { 10, 27, 35, 40, 50 };
    vector<int> vec3 = { 10, 25, 35, 40, 50 };

    cout << "Is " << print_vector(vec1) << " equal to " << print_vector(vec2)
         << " ? " << algorithms::equal(vec1.begin(), vec1.end(), vec2.begin()) << endl;
    cout << "Is " << print_vector(vec1) << " equal to " << print_vector(vec3)
         << " ? " << algorithms::equal(vec1.begin(), vec1.end(), vec3.begin()) << endl << endl;

    vector<int> vec4 = { 35, 40 };
    cout << "Search " << print_vector(vec4) << " in " << print_vector(vec2) << " => "
         << *algorithms::search(vec2.begin(), vec2.end(), vec4.begin(), vec4.end()) << endl << endl;

    cout << "Find 35 in " << print_vector(vec1) << " => " << *algorithms::find(vec1.begin(), vec1.end(), 35) << endl << endl;

    cout << "Find if 40 in " << print_vector(vec1) << " => " << *algorithms::find_if(vec1.begin(), vec1.end(), is_40) << endl << endl;

    vector<int> vec5 = { 10, 20 };
    cout << "Copy " << print_vector(vec1) << " into " << print_vector(vec5) << " => ";
    algorithms::copy(vec1.begin(), vec1.end(), back_inserter(vec5));
    cout << print_vector(vec5) << endl << endl;

    vector<int> vec6;
    cout << "Copy " << print_vector(vec1) << " and remove 35 " << " => ";
    algorithms::remove_copy(vec1.begin(), vec1.end(), back_inserter(vec6), 35);
    cout << print_vector(vec6) << endl << endl;

    vector<int> vec7;
    cout << "Copy " << print_vector(vec1) << " and remove element if equal to 40 " << " => ";
    algorithms::remove_copy_if(vec1.begin(), vec1.end(), back_inserter(vec7), is_40);
    cout << print_vector(vec7) << endl << endl;

    cout << "Remove from " << print_vector(vec5) << " elements not equal to 10 " << " => ";
    cout << print_vector(vec5.begin(), algorithms::remove(vec5.begin(), vec5.end(), 10)) << endl << endl;

    vector<int> vec8;
    cout << "Transform " << print_vector(vec5) << " by detracting 5 from each element " << " => ";
    algorithms::transform(vec5.begin(), vec5.end(), back_inserter(vec8), minus_5);
    cout << print_vector(vec8) << endl << endl;

    cout << "Partition " << print_vector(vec1) << " by condition \" divisible by 10 \"" << " => ";
    algorithms::partition(vec1.begin(), vec1.end(), divisible_10);
    cout << print_vector(vec1) << endl << endl;

    cout << "Add " << print_vector(vec1) << " to 15" << " => "
         << algorithms::accumulate(vec1.begin(), vec1.end(), 15) << endl << endl;

    return 0;
}
