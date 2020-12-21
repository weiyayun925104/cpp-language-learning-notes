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
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
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

const string openTagStart = "<";
const string closeTagStart = "</";
const string tagEnd = ">";

string readHTMLFileAsStream(string fileName)
{
    string stream;

    cout << "Opening HTML file " << fileName << '\n';
    ifstream fileReader(fileName + ".html");
    if (!fileReader.is_open())
    {
        cout << "Could not open file!" << '\n';
        return stream;
    }
    else
    {
        cout << "File is opened!\n";
    }

    cout << "Reading file...\n";
    string line;
    while (getline(fileReader, line, '\n'))
    {
        stream += line;
    }

    return stream;
}

int writeHTMLFile(string fileName, const vector<string> &lines)
{
    cout << "Writing file to HTML format..." << '\n';
    ofstream fileWriter(fileName + ".html");
    if (!fileWriter.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    for (vector<string>::const_iterator itr = lines.begin(), end = lines.end(); itr != end; ++itr)
    {
        fileWriter << *itr << '\n';
    }
    return 0;
}

void print(const vector<string> &input)
{
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        cout << *itr << endl;
    }
    cout << '\n';
}

vector<string> mergeChildElements(const vector<string> &input, const string &tagName)
{
    string openingTag = openTagStart + tagName;
    string closingTag = closeTagStart + tagName + tagEnd;
    bool isInMergeRegion = false;

    vector<string> output;
    string currentMerge = "";
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        string itrOpening = itr->substr(0, openingTag.length());
        if (itrOpening == openingTag)
        {
            isInMergeRegion = true;
            output.push_back(*itr);
        }
        else if (isInMergeRegion && *itr == closingTag)
        {
            isInMergeRegion = false;
            if (currentMerge != "")
            {
                output.push_back(currentMerge);
            }
            output.push_back(*itr);
        }
        else if (isInMergeRegion)
        {
            currentMerge += *itr;
        }
        else
        {
            output.push_back(*itr);
        }
    }
    return output;
}

vector<string> parseHTMLStringToVector(const string &htmlDOMStream)
{
    bool isInOpenTag = false;
    bool isInCloseTag = false;

    vector<string> htmlDOM;
    string currentEntry = "";

    for (int i = 0; i < htmlDOMStream.length(); i++)
    {
        string currentLetter(1, htmlDOMStream[i]);

        string previousLetter = "";
        if (i - 1 >= 0)
        {
            previousLetter.push_back(htmlDOMStream[i - 1]);
        }

        string nextLetter = "";
        if (i + 1 < htmlDOMStream.length())
        {
            nextLetter.push_back(htmlDOMStream[i + 1]);
        }

        if (currentLetter + nextLetter == closeTagStart)
        {
            isInCloseTag = true;
            if (currentEntry != "")
            {
                htmlDOM.push_back(currentEntry);
            }
            currentEntry = htmlDOMStream[i];
        }
        else if(currentLetter == openTagStart)
        {
            isInOpenTag = true;
            if (currentEntry != "")
            {
                htmlDOM.push_back(currentEntry);
            }
            currentEntry = htmlDOMStream[i];
        }
        else if (isInOpenTag && previousLetter == tagEnd)
        {
            isInOpenTag = false;
            if (currentEntry != "")
            {
                htmlDOM.push_back(currentEntry);
            }
            currentEntry = htmlDOMStream[i];
        }
        else if (isInCloseTag && currentLetter == tagEnd)
        {
            isInCloseTag = false;
            currentEntry += htmlDOMStream[i];
            if (currentEntry != "")
            {
                htmlDOM.push_back(currentEntry);
            }
            currentEntry = "";
        }
        else
        {
            currentEntry += htmlDOMStream[i];
        }
    }
    return htmlDOM;
}

vector<string> stripTag(const vector<string> &input, const string &tagName)
{
    string openingTag = openTagStart + tagName;
    string closingTag = closeTagStart + tagName + tagEnd;
    bool isInStripRegion = false;

    vector<string> output;
    for(vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        string itrOpening = itr->substr(0, openingTag.length());
        if (!isInStripRegion && itrOpening == openingTag)
        {
            isInStripRegion = true;
        }
        else if (isInStripRegion && *itr == closingTag)
        {
            isInStripRegion = false;
        }
        else
        {
            output.push_back(*itr);
        }
    }
    return output;
}

vector<string> stripTagAttributes(const vector<string> &input, const string &tagName)
{
    string openingTag = openTagStart + tagName;

    vector<string> output;
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        string itrOpening = itr->substr(0, openingTag.length());
        if (itrOpening == openingTag)
        {
            output.push_back(openingTag + tagEnd);
        }
        else
        {
            output.push_back(*itr);
        }
    }
    return output;
}

vector<string> stripText(const vector<string> &input, const string &tagName)
{
    string openingTag = openTagStart + tagName;
    string closingTag = closeTagStart + tagName + tagEnd;
    bool isInStripRegion = false;

    vector<string> output;
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        string itrOpening = itr->substr(0, openingTag.length());
        if (!isInStripRegion && itrOpening == openingTag)
        {
            isInStripRegion = true;
            output.push_back(*itr);
        }
        else if (isInStripRegion && *itr == closingTag)
        {
            isInStripRegion = false;
            output.push_back(*itr);
        }
        else if (!isInStripRegion)
        {
            output.push_back(*itr);
        }
    }
    return output;
}

vector<string> substituteTag(const vector<string> &input, const string &tagName, const string &tagNameSubstitute)
{
    string openingTag = openTagStart + tagName + tagEnd;
    string closingTag = closeTagStart + tagName + tagEnd;

    vector<string> output;
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        if (*itr == openingTag || *itr == closingTag)
        {
            output.push_back(tagNameSubstitute);
        }
        else
        {
            output.push_back(*itr);
        }
    }
    return output;
}

string getLinkURL(const string &hrefTag)
{
    const string hyperlinkURL = "href=";
    int position = hrefTag.find(hyperlinkURL, 0) + hyperlinkURL.length();

    string linkURL = "";
    char endDemaractor;
    if (hrefTag[position] == '\"')
    {
        endDemaractor = '\"';
        position++;
    }
    else
    {
        endDemaractor = ' ';
    }

    for (int i = position; i < hrefTag.length(); i++)
    {
        if (hrefTag[i] == endDemaractor)
        {
            break;
        }
        linkURL += hrefTag[i];
    }
    return linkURL;
}

vector<string> formatBold(const vector<string> &input)
{
    return substituteTag(input, "b", "*");
}

vector<string> formatItalic(const vector<string> &input)
{
    return substituteTag(input, "i", "_");
}

vector<string> formatHyperlink(const vector<string> &input)
{
    const string hyperlink = "a";
    bool insidetag = false;

    string openingTag = openTagStart + hyperlink;
    string closingTag = closeTagStart + hyperlink + tagEnd;

    vector<string> output;
    for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
    {
        string itrOpening = itr->substr(0, openingTag.length());
        if (itrOpening == openingTag)
        {
            insidetag = true;

            string linkURL = getLinkURL(*itr);

            vector<string>::const_iterator next = itr;
            ++next;
            string innerText = *next;

            output.push_back(innerText + "(" + linkURL + ")");
        }
        else if (*itr == closingTag)
        {
            insidetag = false;
        }
        else if (!insidetag)
        {
            output.push_back(*itr);
        }
    }
    return output;
}

int main(int argc, const char *argv[])
{
    try
    {
        string fileName = "sampleHTML";
        string htmlDOMStream = readHTMLFileAsStream(fileName);

        vector<string> htmlDOM = parseHTMLStringToVector(htmlDOMStream);
        const string body = "body";

        cout << "Original HTML: \n";
        vector<string> htmlDOMPrint = mergeChildElements(htmlDOM, body);
        print(htmlDOMPrint);

        const string html = "html";
        htmlDOM = stripTag(htmlDOM, html);

        const string head = "head";
        htmlDOM = stripText(htmlDOM, head);

        htmlDOM = stripTagAttributes(htmlDOM, body);
        htmlDOM = formatBold(htmlDOM);
        htmlDOM = formatItalic(htmlDOM);
        htmlDOM = formatHyperlink(htmlDOM);

        cout << "Parsed HTML:\n";
        htmlDOMPrint = mergeChildElements(htmlDOM, body);
        print(htmlDOMPrint);

        string newFileName = fileName + "_parsed";
        writeHTMLFile(newFileName, htmlDOMPrint);

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
