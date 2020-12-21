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

class XmlNode
{
public:
    char TagOpen() const;
    char CloseTagStart() const;
    char TagClose() const;
    std::string Name() const;
    std::vector<std::string> Attributes();
    std::string AttributeValue(std::string attribute);
    std::string InnerText() const;
    int NumberOfChildren() const;
    XmlNode *Child(int index);

    XmlNode();
    XmlNode(char tagOpen, char tagClose, char nodeClose);
    ~XmlNode();

    static XmlNode *createNode(const std::string &input);
    void nodeStart(const std::string &input);
    std::string print(int level = 0, const std::string &spacer = "");
private:
    const std::string _spacer = "  ";

    char _tagOpen;
    char _closeTagStart;
    char _tagClose;
    std::string _name;
    std::map<std::string, std::string> _attributes;
    std::vector<XmlNode *> _children;
    std::string _innerText;

    void attributeRead(const std::string &attributesStream);
    void nodeTextRead(const std::string &innerText);
    std::string nodeEnd(const std::string &nameNode) const;
    static std::string clearEmpty(std::string &text);
};

char XmlNode::TagOpen() const
{
    return _tagOpen;
}

char XmlNode::CloseTagStart() const
{
    return _closeTagStart;
}

char XmlNode::TagClose() const
{
    return _tagClose;
}

string XmlNode::Name() const
{
    return _name;
}

vector<string> XmlNode::Attributes()
{
    vector<string> attributeKeys;
    for (map<string, string>::iterator itr = _attributes.begin(), end = _attributes.end(); itr != end; ++itr)
    {
        attributeKeys.push_back(itr->first);
    }
    return attributeKeys;
}

string XmlNode::AttributeValue(string attribute)
{
    return _attributes[attribute];
}

string XmlNode::InnerText() const
{
    return _innerText;
}

int XmlNode::NumberOfChildren() const
{
    return _children.size();
}

XmlNode *XmlNode::Child(int index)
{
    return _children[index];
}

XmlNode::XmlNode()
{
    _tagOpen = '<';
    _closeTagStart = '/';
    _tagClose = '>';
}

XmlNode::XmlNode(char tagOpen, char tagClose, char nodeClose)
{
    _tagOpen = tagOpen;
    _tagClose = tagClose;
    _closeTagStart = nodeClose;
}

XmlNode::~XmlNode()
{
    for (vector<XmlNode *>::iterator itr = _children.begin(), end = _children.end(); itr != end; ++itr)
    {
        delete *itr;
    }
    _children.clear();
}

XmlNode *XmlNode::createNode(const string &input)
{
    XmlNode *node = new XmlNode();
    node->nodeStart(input);
    return node;
}

void XmlNode::nodeStart(const string &input)
{
    int startTagOpenIndex = input.find_first_of(_tagOpen);
    int spaceIndex = input.find_first_of(' ', startTagOpenIndex);
    int startTagCloseIndex = input.find_first_of(_tagClose, startTagOpenIndex);
    if (spaceIndex != string::npos && spaceIndex < startTagCloseIndex)
    {
        _name = input.substr(startTagOpenIndex + 1, (spaceIndex - 1) - startTagOpenIndex);
        attributeRead(input.substr(spaceIndex + 1, (startTagCloseIndex - 1) - spaceIndex));
    }
    else
    {
        _name = input.substr(startTagOpenIndex + 1, (startTagCloseIndex - 1) - startTagOpenIndex);
    }

    string closeTag = nodeEnd(_name);
    int endTagOpenIndex = input.find_last_of(closeTag);
    string innerText = input.substr( startTagCloseIndex + 1, (endTagOpenIndex - 1) - startTagCloseIndex - ( closeTag.length() - 1 ) );
    nodeTextRead(innerText);
}

void XmlNode::attributeRead(const string &attributesStream)
{
    string currentKey = "";
    string currentEntry = "";
    bool isInValue = false;
    for (int i = 0; i < attributesStream.length(); i++)
    {
        if (attributesStream[i] == '=')
        {
            currentKey = currentEntry;
            currentEntry.clear();
        }
        else if (attributesStream[i] == '"' && !isInValue)
        {
            isInValue = true;
        }
        else if (attributesStream[i] == '"' && isInValue)
        {
            isInValue = false;
            currentEntry = clearEmpty(currentEntry);
            _attributes[currentKey] = currentEntry;
            currentKey.clear();
            currentEntry.clear();
        }
        else if (attributesStream[i] != '=' &&
                 attributesStream[i] != '"' &&
                 !(attributesStream[i] == ' ' && !isInValue))
        {
            currentEntry += attributesStream[i];
        }
    }
}

void XmlNode::nodeTextRead(const string &innerText)
{
    int startTagOpenIndex = innerText.find_first_of(_tagOpen);
    if (startTagOpenIndex == string::npos)
    {
        _innerText = innerText;
        _innerText = clearEmpty(_innerText);
        return;
    }

    _innerText += innerText.substr(0, startTagOpenIndex);
    int openTagCount = 0;
    int tagCount = 0;
    string innerInnerText;
    for (int i = startTagOpenIndex; i < innerText.length(); i++)
    {
        char currentCharacter = innerText[i];
        if (currentCharacter == _tagOpen)
        {
            tagCount++;
            if ( (i + 1) < innerText.length() && innerText[i + 1] == _closeTagStart)
            {
                openTagCount--;
            }
            else
            {
                openTagCount++;
            }
        }
        else if (currentCharacter == _tagClose)
        {
            tagCount--;
        }

        if (openTagCount == 0 && tagCount == 0 && currentCharacter != _tagClose)
        {
            _innerText.push_back(currentCharacter);
        }
        else
        {
            innerInnerText.push_back(currentCharacter);
        }

        if (currentCharacter == _tagClose && openTagCount == 0)
        {
            _children.push_back(createNode(innerInnerText));
            innerInnerText.clear();
        }
    }
    _innerText = clearEmpty(_innerText);
}


string XmlNode::nodeEnd(const string &nameNode) const
{
    string nodeEndTag;
    nodeEndTag.push_back(_tagOpen);
    nodeEndTag.push_back(_closeTagStart);
    return (nodeEndTag + nameNode + _tagClose);
}

string XmlNode::print(int level, const string &spacer)
{
    string tabs = "";
    string currentSpacer;
    spacer.empty() ? currentSpacer = _spacer : currentSpacer = spacer;
    for (int i = 0; i < level; i++)
    {
        tabs += currentSpacer;
    }
    string currentNode = tabs;

    currentNode.push_back(_tagOpen);
    currentNode += _name;
    vector<string> attributes = Attributes();
    for (vector<string>::iterator itr = attributes.begin(), end = attributes.end(); itr != end; ++itr)
    {
        currentNode += " " + *itr + "=\"" + _attributes[*itr] + "\"";
    }
    currentNode += _tagClose;

    if (!_innerText.empty())
    {
        currentNode += '\n' + tabs + currentSpacer;
        currentNode += _innerText;
    }

    int children = NumberOfChildren();
    for (int i = 0; i < children; i++)
    {
        currentNode += '\n';
        currentNode += _children[i]->print(level + 1);
    }

    currentNode += '\n' + tabs;
    currentNode += nodeEnd(_name);

    return currentNode;
}

string XmlNode::clearEmpty(string &text)
{
    if (text.find_first_not_of(' ') == string::npos)
    {
        return "";
    }
    return text;
}

string readXMLFileAsStream(string &fileName)
{
    cout << "Opening XML file " << fileName << '\n';
    ifstream fileReader(fileName + ".xml");
    if (!fileReader.is_open())
    {
        cout << "Could not open file!" << '\n';
        return "";
    }
    cout << "File is opened!\n";

    cout << "Reading file...\n";
    string stream;
    string line;
    while (getline(fileReader, line, '\n'))
    {
        stream += line;
    }

    return stream;
}

int main(int argc, const char *argv[])
{
    try
    {
        string xmlToString;
        string xmlDOMStream;
        string fileName;
        XmlNode *root;
        vector<string> fileNames =
        {
            "addresses",
            "books",
            "attributesSample"
        };

        for(vector<string>::iterator itr = fileNames.begin(), end = fileNames.end(); itr != end; ++itr)
        {
            cout << "Reading & parsing " << *itr << ".xml\n";
            xmlDOMStream = readXMLFileAsStream(*itr);
            if (!xmlDOMStream.empty())
            {
                root = XmlNode::createNode(xmlDOMStream);
                cout << "Printing XML object...\n\n";
                xmlToString = root->print();
                cout << xmlToString;
                delete root;
            }
            cout << "\n\n";
        }

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
