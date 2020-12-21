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

enum Direction
{
    North,
    South,
    East,
    West
};

struct Position
{
    int row;
    int column;
};

struct Cell
{
    enum Wall
    {
        Wall_North = 0x0008,
        Wall_South = 0x0002,
        Wall_East = 0x0004,
        Wall_West = 0x0001,
        Wall_All = 0x000f,
        Wall_None = 0x0000
    };

    struct Position position;
    int walls;

    int getWalls() const
    {
        return walls & Wall_All;
    }
    void setWalls(const int w)
    {
        walls = w & Wall_All;
    }
    void removeWall(const int w)
    {
        if (w != Wall_North && w != Wall_East && w != Wall_South && w != Wall_West)
        {
            return;
        }
        walls &= ~w;
    }


    string print() const
    {
        string cell = "<";
        if ( ( getWalls() & Wall_West ) != 0 )
        {
            cell += 'W';
        }
        else
        {
            cell += " ";
        }

        if ( ( getWalls() & Wall_South ) != 0 )
        {
            cell += 'S';
        }
        else
        {
            cell += " ";
        }

        if ( ( getWalls() & Wall_North ) != 0 )
        {
            cell += 'N';
        }
        else
        {
            cell += " ";
        }

        if ( ( getWalls() & Wall_East ) != 0 )
        {
            cell += 'E';
        }
        else
        {
            cell += " ";
        }
        cell += ">";
        return cell;
    }
};

struct VectorCell
{
    Cell *array = nullptr;
    int size = 0;
    int maxSize = 0;

    bool isEmpty() const
    {
        return (size == 0);
    }

    void clear()
    {
        size = 0;
        maxSize = 0;
        if (array != nullptr)
        {
            delete[] array;
            array = nullptr;
        }
    }

    void pushBack(Cell *cell)
    {
        if (size == maxSize)
        {
            if (maxSize == 0)
            {
                Cell *p_newvalues = new Cell[8];
                p_newvalues[size] = *cell;
                if (array != nullptr)
                {
                    delete[] array;
                    array = nullptr;
                }
                array = p_newvalues;
                size++;
                maxSize = 8;
            }
            else
            {
                Cell *p_newvalues = new Cell[maxSize * 2];
                for (int i = 0; i < size; i++)
                {
                    p_newvalues[i] = array[i];
                }
                p_newvalues[size] = *cell;
                if (array != nullptr)
                {
                    delete[] array;
                    array = nullptr;
                }
                array = p_newvalues;
                size++;
                maxSize *= 2;
            }
        }
        else
        {
            array[size] = *cell;
            size++;
        }
    }

    void popBack()
    {
        if (size > 0)
        {
            size--;
            if (size == 0)
            {
                clear();
            }
        }
    }
};

struct VectorDirection
{
    Direction *array = nullptr;
    int size = 0;
    int maxSize = 0;

    bool isEmpty() const
    {
        return (size == 0);
    }

    void clear()
    {
        size = 0;
        maxSize = 0;
        if (array != nullptr)
        {
            delete[] array;
            array = nullptr;
        }
    }

    void pushBack(Direction direction)
    {
        if (size == maxSize)
        {
            if (maxSize == 0)
            {
                Direction *p_newvalues = new Direction[8];
                p_newvalues[size] = direction;
                if (array != nullptr)
                {
                    delete[] array;
                    array = nullptr;
                }
                array = p_newvalues;
                size++;
                maxSize = 8;
            }
            else
            {
                Direction *p_newvalues = new Direction[maxSize * 2];
                for (int i = 0; i < size; i++)
                {
                    p_newvalues[i] = array[i];
                }
                p_newvalues[size] = direction;
                if (array != nullptr)
                {
                    delete[] array;
                    array = nullptr;
                }
                array = p_newvalues;
                size++;
                maxSize *= 2;
            }
        }
        else
        {
            array[size] = direction;
            size++;
        }
    }

    void popBack()
    {
        if (size > 0)
        {
            size--;
            if (size == 0)
            {
                clear();
            }
        }
    }
};

int main(int argc, const char *argv[])
{
    try
    {
        srand( time(nullptr) );

        int mazeWidth = 6;
        int mazeHeight = 6;

        do
        {
            mazeWidth = 6;
            mazeHeight = 6;
            cout << "Please specify the dimensions of the maze (at least 6x6):\n";
            cout << "Width: ";
            cin >> mazeWidth;
            cin.clear();
            cin.ignore(80, '\n');

            cout << "Height: ";
            cin >> mazeHeight;
            cin.clear();
            cin.ignore(80, '\n');

            cout << '\n';
        }
        while ( (mazeWidth < 6) || (mazeHeight < 6) );

        Cell **maze = new Cell*[mazeWidth];
        for (int i = 0; i < mazeWidth; i++)
        {
            maze[i] = new Cell[mazeHeight];
        }

        for (int row = 0; row < mazeWidth; row++)
        {
            for (int column = 0; column < mazeHeight; column++)
            {
                maze[row][column].position.row = row;
                maze[row][column].position.column = column;
                maze[row][column].setWalls(Cell::Wall_All);
            }
        }

        int currentRow = rand() % mazeWidth;
        int currentColumn = rand() % mazeHeight;

        VectorCell trail;
        trail.pushBack( & ( maze[currentRow][currentColumn] ) );

        VectorDirection currentDirections;

        while ( !trail.isEmpty() )
        {
            currentDirections.clear();
            if (currentColumn > 0)
            {
                if (maze[currentRow][currentColumn - 1].getWalls() == Cell::Wall_All)
                {
                    currentDirections.pushBack(West);
                }
            }

            if (currentColumn < mazeHeight - 1)
            {
                if (maze[currentRow][currentColumn + 1].getWalls() == Cell::Wall_All)
                {
                    currentDirections.pushBack(East);
                }
            }

            if (currentRow > 0)
            {
                if (maze[currentRow - 1][currentColumn].getWalls() == Cell::Wall_All)
                {
                    currentDirections.pushBack(North);
                }
            }

            if (currentRow < mazeWidth - 1)
            {
                if (maze[currentRow + 1][currentColumn].getWalls() == Cell::Wall_All)
                {
                    currentDirections.pushBack(South);
                }
            }

            if ( !currentDirections.isEmpty() )
            {
                int randomDirectionIndex = rand() % currentDirections.size;

                switch (currentDirections.array[randomDirectionIndex])
                {
                case North:
                    maze[currentRow][currentColumn].removeWall(Cell::Wall_North);
                    maze[currentRow - 1][currentColumn].removeWall(Cell::Wall_South);
                    --currentRow;
                    break;
                case South:
                    maze[currentRow][currentColumn].removeWall(Cell::Wall_South);
                    maze[currentRow + 1][currentColumn].removeWall(Cell::Wall_North);
                    ++currentRow;
                    break;
                case East:
                    maze[currentRow][currentColumn].removeWall(Cell::Wall_East);
                    maze[currentRow][currentColumn + 1].removeWall(Cell::Wall_West);
                    ++currentColumn;
                    break;
                case West:
                    maze[currentRow][currentColumn].removeWall(Cell::Wall_West);
                    maze[currentRow][currentColumn - 1].removeWall(Cell::Wall_East);
                    --currentColumn;
                    break;
                default:
                    break;
                }

                trail.pushBack( & ( maze[currentRow][currentColumn] ) );
            }
            else
            {
                trail.popBack();

                if ( !trail.isEmpty() )
                {
                    currentRow = trail.array[trail.size - 1].position.row;
                    currentColumn = trail.array[trail.size - 1].position.column;
                }
            }
        }


        for (int row = 0; row < mazeWidth; row++)
        {
            for (int column = 0; column < mazeHeight; column++)
            {
                if (column != 0)
                {
                    cout << ", ";
                }
                cout << maze[row][column].print();
            }
            cout << "\n";
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
