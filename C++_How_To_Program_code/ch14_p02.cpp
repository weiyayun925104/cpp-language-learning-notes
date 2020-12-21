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
using std::ios;
using std::ios_base;
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

vector<int> readBinaryFile(string fileName)
{
    cout << "Opening binary file " << fileName << '\n';
    ifstream aFile(fileName + ".bin", ios::binary);
    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        vector<int> scoresEmpty;
        return scoresEmpty;
    }
    else
    {
        cout << "File is opened!\n";
    }

    cout << "Reading file...\n";

    int numberOfScores;
    if( !aFile.read( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error reading from file." << endl;
        vector<int> scoresEmpty;
        return scoresEmpty;
    }

    vector<int> scores(numberOfScores);
    aFile.read( reinterpret_cast<char *>(&scores[0]), numberOfScores * sizeof(int) );

    return scores;
}

vector<int> readTextFile(string fileName)
{
    cout << "Opening text file " << fileName << '\n';
    ifstream fileReader(fileName + ".txt");
    if (!fileReader.is_open())
    {
        cout << "Could not open file!" << '\n';
        vector<int> scoresEmpty;
        return scoresEmpty;
    }
    else
    {
        cout << "File is opened!\n";
    }

    cout << "Reading file...\n";
    vector<int> scores;
    int score;
    while (fileReader >> score)
    {
        scores.push_back(score);
    }

    return scores;
}

int writeBinaryFile(string fileName, const vector<int> &scores)
{
    if (scores.size() <= 0)
    {
        cout << "Vector is empty.\n";
        return 0;
    }
    cout << "Writing file to binary format..." << '\n';
    ofstream aFile(fileName + ".bin", ios::trunc | ios::binary );
    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    int numberOfScores = scores.size();
    if ( !aFile.write( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error writing to file." << endl;
        return 1;
    }
    aFile.write( reinterpret_cast<const char *>(&scores[0]), numberOfScores * sizeof(int) );

    return 0;
}

int writeTextFile(string fileName, const vector<int> &scores)
{
    if (scores.size() <= 0)
    {
        cout << "Vector is empty.\n";
        return 0;
    }
    cout << "Writing file to text format..." << '\n';
    ofstream fileWriter(fileName + ".txt", ios::trunc);
    if (!fileWriter.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    for (vector<int>::const_iterator itr = scores.begin(), end = scores.end(); itr != end; ++itr)
    {
        fileWriter << *itr << '\n';
    }

    return 0;
}

int insertBinaryFile(string fileName)
{
    cout << "Inserting data into binary file..." << '\n';
    fstream aFile(fileName + ".bin", ios::binary | ios::out | ios::in);

    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    int newHighScore;
    cout << "Enter a new high score: ";
    cin >> newHighScore;

    int numberOfScores;
    if ( !aFile.read( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error reading from file." << endl;
        return 1;
    }

    streampos preScorePosition = aFile.tellg();
    int currentScore = 0;
    while ( aFile.read( reinterpret_cast<char *>(&currentScore), sizeof(currentScore) ) )
    {
        if (currentScore < newHighScore)
        {
            break;
        }
        preScorePosition = aFile.tellg();
    }

    if ( !aFile.eof() && aFile.fail() )
    {
        cout << "Bad score, could not read, exit.\n";
        return 1;
    }

    aFile.clear();

    aFile.seekg(preScorePosition);

    vector<int> scores;
    while ( aFile.read( reinterpret_cast<char *>(&currentScore), sizeof(currentScore) ) )
    {
        scores.push_back(currentScore);
    }

    if ( !aFile.eof() && aFile.fail() )
    {
        cout << "Bad score, could not read, exit.\n";
        return 1;
    }

    aFile.clear();

    aFile.seekp(preScorePosition);

    aFile.write( reinterpret_cast<char *>(&newHighScore), sizeof(newHighScore) );
    if (scores.size() > 0)
    {
        aFile.write( reinterpret_cast<char *>(&scores[0]), scores.size() * sizeof(int) );
    }

    numberOfScores++;
    aFile.seekp(0, ios_base::beg);
    if ( !aFile.write( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error writing to file." << endl;
        return 1;
    }

    return 0;
}

void print(const vector<int> &scores)
{

    cout << "File contents are: \n";
    for (vector<int>::const_iterator itr = scores.begin(), end = scores.end(); itr != end; ++itr)
    {
        cout << *itr << '\n';
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        string fileName = "highScores";
        cout << "Writing base file " << fileName << '\n';
        vector<int> scores
        {
            1000,
            987,
            864,
            766,
            744,
            500,
            453,
            321,
            201,
            98,
            5
        };
        writeTextFile(fileName, scores);
        writeBinaryFile(fileName, scores);
        print(scores);

        if (insertBinaryFile(fileName) != 0)
        {
            cout << "Error inserting into binary file. Program will exit...\n";
            return 1;
        }

        vector<int> newScores = readBinaryFile(fileName);
        writeTextFile(fileName, newScores);
        print(newScores);

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
