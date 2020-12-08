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

string getOneDigitNumber(char number);
string getTeensNumber(char number);
string getTensNumber(char number);
string getTwoDigitNumber(char ten, char one);
string getThreeDigitNumber(char hundred, char ten, char one);
string getMagnitude(int divisionsOfThree);

int main()
{
    int i;

    cout << "Please enter an integer number: ";
    cin >> i;
    string numberAsString = to_string(i);

    string sign = "";
    bool isNegative = (numberAsString.at(0) == '-');
    if (isNegative)
    {
        sign = "Negative ";
    }

    int signOffset = 0;
    if (isNegative)
    {
        signOffset = 1;
    }

    int numberCount = numberAsString.length() - signOffset;

    string numberInEnglish = "";
    int tens = numberCount % 3;
    int divisionsOfThree = (numberCount - 1) / 3;

    if ( numberCount <= 3 )
    {
        switch (numberCount)
        {
        case 1:
            if ( numberAsString.at(signOffset) == '0' )
            {
                numberInEnglish = "zero";
            }
            else
            {
                numberInEnglish = getOneDigitNumber(numberAsString.at(signOffset));
            }
            break;
        case 2:
            numberInEnglish = getTwoDigitNumber(numberAsString.at(signOffset), numberAsString.at(signOffset + 1));
            break;
        case 3:
            numberInEnglish = getThreeDigitNumber(numberAsString.at(signOffset), numberAsString.at(signOffset + 1), numberAsString.at(signOffset + 2));
            break;
        default:
            break;
        }
        cout << numberAsString << ": " << sign << numberInEnglish << '\n';
        return 0;
    }

    if ( tens > 0 )
    {
        switch (tens)
        {
        case 1:
            numberInEnglish = getOneDigitNumber(numberAsString.at(signOffset));
            break;
        case 2:
            numberInEnglish = getTwoDigitNumber(numberAsString.at(signOffset), numberAsString.at(signOffset + 1));
            break;
        default:
            break;
        }
        numberInEnglish += " " + getMagnitude(divisionsOfThree);
        divisionsOfThree--;
    }

    for (size_t j = tens + signOffset; j < numberAsString.length(); j += 3)
    {
        string threeDigits = numberAsString.substr(j, 3);
        if (threeDigits != "000")
        {
            if(numberInEnglish.length() > 0)
            {
                numberInEnglish += ", ";
            }
            if (divisionsOfThree == 0)
            {
                numberInEnglish +=
                    getThreeDigitNumber(threeDigits.at(0), threeDigits.at(1), threeDigits.at(2));
            }
            else
            {
                numberInEnglish +=
                    getThreeDigitNumber(threeDigits.at(0), threeDigits.at(1), threeDigits.at(2)) + " " + getMagnitude(divisionsOfThree);
            }
        }

        divisionsOfThree--;
    }
    cout << numberAsString << ": " << sign << numberInEnglish << '\n';

}

string getOneDigitNumber(char number)
{
    switch(number)
    {
    case '1':
        return "one";
    case '2':
        return "two";
    case '3':
        return "three";
    case '4':
        return "four";
    case '5':
        return "five";
    case '6':
        return "six";
    case '7':
        return "seven";
    case '8':
        return "eight";
    case '9':
        return "nine";
    default:
        return "";
    }
}

string getTeensNumber(char number)
{
    switch (number)
    {
    case '0':
        return "ten";
    case '1':
        return "eleven";
    case '2':
        return "twelve";
    case '3':
        return "thirteen";
    case '4':
        return "fourteen";
    case '5':
        return "fifteen";
    case '6':
        return "sixteen";
    case '7':
        return "seventeen";
    case '8':
        return "eighteen";
    case '9':
        return "nineteen";
    default:
        return "";
    }
}

string getTensNumber(char number)
{
    switch (number)
    {
    case '2':
        return "twenty";
    case '3':
        return "thirty";
    case '4':
        return "fourty";
    case '5':
        return "fifty";
    case '6':
        return "sixty";
    case '7':
        return "seventy";
    case '8':
        return "eighty";
    case '9':
        return "ninety";
    default:
        return "";
    }
}

string getTwoDigitNumber(char ten, char one)
{
    if (ten == '0')
    {
        return  getOneDigitNumber(one);
    }
    else if (ten == '1')
    {
        return getTeensNumber(one);
    }
    else
    {
        if (one == '0')
        {
            return getTensNumber(ten);
        }
        else
        {
            return (getTensNumber(ten) + " " + getOneDigitNumber(one));
        }
    }
}

string getThreeDigitNumber(char hundred, char ten, char one)
{
    if (hundred == '0')
    {
        return  getTwoDigitNumber(ten, one);
    }
    else
    {
        if (ten == '0' && one == '0')
        {
            return (getOneDigitNumber(hundred) + " hundred");
        }
        else
        {
            return (getOneDigitNumber(hundred) + " hundred " + getTwoDigitNumber(ten, one));
        }
    }
}

string getMagnitude(int divisionsOfThree)
{
    switch (divisionsOfThree)
    {
    case 1:
        return "thousand";
    case 2:
        return "million";
    case 3:
        return "billion";
    case 4:
        return "trillion";
    default:
        return "";
    }
}
