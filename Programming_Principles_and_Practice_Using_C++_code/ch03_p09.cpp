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

bool isNegative(string number);

string wordsToNumbers(string word);
bool isTens(string word);
string getTens(string numberAsWord);
bool isHundreds(string word);
string getHundreds(string numberAsWord);
int getMagnitudeBalance(string currentWord, string numberAsString);
string getPaddedForMagnitude(string numberAsString,	int magnitudeBalance);

bool isNumberDemarcator(char character);
bool isFirstLetter(string numberInEnglish,	int numberIndexFromEnd);
int wordsToMagnitude(string word);

string addZeroPadding(int numberOfZeroes);
string addCommasMagnitude(string numberAsWord);

char const space = ' ';
char const comma = ',';
char const hyphen = '-';

int main()
{
    string numberInEnglish = "";
    cout << "Please write in any number you wish to see written out in digits: " << '\n';
    while (getline(cin, numberInEnglish, '\n') && numberInEnglish != "")
    {
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
        if (numberAsString == "")
        {
            cout << "The number you entered was not a number I know\n";
        }
        else
        {
            numberAsString = addCommasMagnitude(numberAsString);

            if (isNegative(numberInEnglish))
            {
                numberAsString = "-" + numberAsString;
            }
            cout << "The number you entered was " << numberAsString << '\n';
        }
        cout << "Please write in any number you wish to see written out in digits: " << '\n';
    }
}

bool isNumberDemarcator(char character)
{
    return ( (character == hyphen) ||
             (character == comma) ||
             (character == space) );
}

bool isFirstLetter(string numberInEnglish,
                   int numberIndexFromEnd)
{
    return ( numberIndexFromEnd == numberInEnglish.length() - 1 );
}

bool isNegative(string number)
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

string wordsToNumbers(string word)
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

bool isTens(string word)
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

string getTens(string numberAsWord)
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

bool isHundreds(string word)
{
    return (word == "hundred");
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

int getMagnitudeBalance(string currentWord,
                        string numberAsString)
{
    int currentMagnitude = wordsToMagnitude(currentWord);
    int numberLength = numberAsString.length();
    return (currentMagnitude - numberLength);
}


string getPaddedForMagnitude(string numberAsString,
                             int magnitudeBalance)
{
    return (addZeroPadding(magnitudeBalance) + numberAsString);
}


int wordsToMagnitude(string word)
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

string addCommasMagnitude(string numberAsWord)
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
