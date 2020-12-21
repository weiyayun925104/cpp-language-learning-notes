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

char const space = ' ';
char const comma = ',';
char const hyphen = '-';

bool isNumberDemarcator(char character)
{
    return ( (character == hyphen) ||
             (character == comma) ||
             (character == space) );
}

bool isFirstLetter(const string & numberInEnglish, int numberIndexFromEnd)
{
    return ( numberIndexFromEnd == numberInEnglish.length() - 1 );
}

bool isNegative(const string & number)
{
    string negative = "negative";
    if (number.length() > negative.length())
    {
        for (size_t i = 0; i < negative.length(); i++)
        {
            if (!(tolower(number[i]) == negative[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isTens(const string & word)
{
    return ((word == "twenty") ||
            (word == "thirty") ||
            (word == "forty") ||
            (word == "fifty") ||
            (word == "sixty") ||
            (word == "seventy") ||
            (word == "eighty") ||
            (word == "ninety"));
}

bool isHundreds(const string & word)
{
    return (word == "hundred");
}

string wordsToNumbers(const string & word)
{
    if (word == "zero")
        return "0";
    if (word == "one")
        return "1";
    if (word == "two")
        return "2";
    if (word == "three")
        return "3";
    if (word == "four")
        return "4";
    if (word == "five")
        return "5";
    if (word == "six")
        return "6";
    if (word == "seven")
        return "7";
    if (word == "eight")
        return "8";
    if (word == "nine")
        return "9";
    if (word == "ten")
        return "10";
    if (word == "eleven")
        return "11";
    if (word == "twelve")
        return "12";
    if (word == "thirteen")
        return "13";
    if (word == "fourteen")
        return "14";
    if (word == "fifteen")
        return "15";
    if (word == "sixteen")
        return "16";
    if (word == "seventeen")
        return "17";
    if (word == "eighteen")
        return "18";
    if (word == "nineteen")
        return "19";
    if (word == "twenty")
        return "2";
    if (word == "thirty")
        return "3";
    if (word == "forty")
        return "4";
    if (word == "fifty")
        return "5";
    if (word == "sixty")
        return "6";
    if (word == "seventy")
        return "7";
    if (word == "eighty")
        return "8";
    if (word == "ninety")
        return "9";
    return "";
}

int wordsToMagnitude(const string & word)
{
    if (word == "thousand")
    {
        return 3;
    }
    if (word == "million")
    {
        return 6;
    }
    if (word == "billion")
    {
        return 9;
    }
    if (word == "trillion")
    {
        return 12;
    }
    return 0;
}

string addZeroPadding(int numberOfZeroes)
{
    string currentPadding = "";
    for (size_t j = 0; j < numberOfZeroes; j++)
    {
        currentPadding += "0";
    }
    return currentPadding;
}

string addCommasMagnitude(const string & numberAsWord)
{
    string numberAsWordWithCommas = "";
    int subcount = 0;
    int originalLength = numberAsWord.length();
    for (size_t i = 0; i < originalLength; i++)
    {
        numberAsWordWithCommas = numberAsWord[originalLength - 1 - i] + numberAsWordWithCommas;
        subcount++;
        if ((subcount == 3) && !(i == originalLength - 1))
        {
            subcount = 0;
            numberAsWordWithCommas = "," + numberAsWordWithCommas;
        }
    }
    return numberAsWordWithCommas;
}

string getTens(string  numberAsWord)
{
    int numberLength = numberAsWord.length();
    if (numberLength < 2)
    {
        numberAsWord = addZeroPadding(1 - numberLength) + numberAsWord;
    }
    else
    {
        int offset = 1;
        while (offset - numberLength < 0)
        {
            offset += 3;
        }
        numberAsWord = addZeroPadding(offset - numberLength) + numberAsWord;
    }
    return numberAsWord;
}

string getHundreds(string numberAsWord)
{
    int numberLength = numberAsWord.length();

    int offset = 2;
    while (offset - numberLength < 0)
    {
        offset += 3;
    }
    numberAsWord = addZeroPadding(offset - numberLength) + numberAsWord;

    return numberAsWord;
}

int getMagnitudeBalance(const string & currentWord, const string & numberAsString)
{
    int currentMagnitude = wordsToMagnitude(currentWord);
    int numberLength = numberAsString.length();
    return (currentMagnitude - numberLength);
}


string getPaddedForMagnitude(const string & numberAsString, int magnitudeBalance)
{
    return (addZeroPadding(magnitudeBalance) + numberAsString);
}

int main(int argc, const char *argv[])
{
    try
    {
        string numberInEnglish = "";
        cout << "Please write in any number you wish to see written out in digits: " << '\n';
        getline(cin, numberInEnglish, '\n');

        string numberAsString = "";
        string currentWord = "";
        for (size_t i = 0; i < numberInEnglish.length(); i++)
        {
            char currentLetter = tolower(numberInEnglish[numberInEnglish.length() - 1 - i]);

            if (!isNumberDemarcator(currentLetter))
            {
                currentWord = currentLetter + currentWord;
            }

            if ( !(currentWord == "") && ( isNumberDemarcator(currentLetter) || isFirstLetter(numberInEnglish, i) ) )
            {
                int magnitudeBalance;

                if (isTens(currentWord))
                {
                    numberAsString = getTens(numberAsString);
                }
                else if (isHundreds(currentWord))
                {
                    numberAsString = getHundreds(numberAsString);
                }
                else if ( ( magnitudeBalance = getMagnitudeBalance(currentWord, numberAsString) ) > 0 )
                {
                    numberAsString = getPaddedForMagnitude(numberAsString, magnitudeBalance);
                }
                string currentNumber = wordsToNumbers(currentWord);

                if (!(currentNumber == ""))
                {
                    numberAsString = currentNumber + numberAsString;
                }

                currentWord = "";
            }
        }

        numberAsString = addCommasMagnitude(numberAsString);

        if (isNegative(numberInEnglish))
        {
            numberAsString = "-" + numberAsString;
        }
        cout << "The number you entered was " << numberAsString << '\n';

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
