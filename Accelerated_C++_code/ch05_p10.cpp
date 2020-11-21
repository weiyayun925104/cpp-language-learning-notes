#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::string;


bool is_palindrome(const string &s)
{
    string::const_iterator iter = s.begin();
    string::const_reverse_iterator r_iter = s.rbegin();

    while (iter != r_iter.base() && iter + 1 != r_iter.base())
    {
        if (tolower(*iter++) != tolower(*r_iter++))
        {
            return false;
        }
    }

    return true;
}

vector<string> get_palindromes(const vector<string> &v)
{
    vector<string> p;
    vector<string>::const_iterator iter = v.begin();

    while (iter != v.end())
    {
        if (is_palindrome(*iter))
        {
            p.push_back(*iter);
        }
        ++iter;
    }

    return p;
}

ostream &write_palindromes(ostream &os, const vector<string> &v)
{
    vector<string> palindromes = get_palindromes(v);

    for (vector<string>::size_type i = 0; i < palindromes.size(); i++)
    {
        os << palindromes[i] << endl;
    }

    return os;
}

int main()
{
    vector<string> words = { "TEST", "teet", "racecar", "BIKE", "six", "madam", "EIGHT", "reDder", "ten" };
    write_palindromes(cout, words);

    return 0;
}
