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

enum SquareState
{
    TTTS_Blank,
    TTTS_O,
    TTTS_X
};

struct Position
{
    int row;
    int column;
};

struct TicTacToeSquare
{
    SquareState state;
    Position position;
    TicTacToeSquare *next;
    TicTacToeSquare *previous;
};

int const minToWin = 4;

TicTacToeSquare *addToLinkedList(TicTacToeSquare *p_list, int row, int column, SquareState state)
{
    TicTacToeSquare *p_item = new TicTacToeSquare;
    p_item->position.row = row;
    p_item->position.column = column;
    p_item->state = state;

    p_item->previous = nullptr;
    p_item->next = p_list;
    if (p_list != nullptr)
    {
        p_list->previous = p_item;
    }

    return p_item;
}

TicTacToeSquare *createGameBoard(int size)
{
    TicTacToeSquare *p_item = nullptr;
    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            p_item = addToLinkedList(p_item, row, column, TTTS_Blank);
        }
    }
    return p_item;
}

TicTacToeSquare *getSquare(Position boardPosition, TicTacToeSquare *gameBoard)
{
    TicTacToeSquare *p_current = gameBoard;
    while (p_current != nullptr)
    {
        if ( (p_current->position.row == boardPosition.row) &&
                (p_current->position.column == boardPosition.column) )
        {
            return p_current;
        }
        p_current = p_current->next;
    }
    return nullptr;
}

string setPlayer(bool playerXInSession)
{
    if (playerXInSession)
    {
        return "X";
    }
    return "O";
}

bool validIndex(Position boardPosition, int boardSize)
{
    return ( ( (boardPosition.row >= 0) && (boardPosition.column >= 0) ) &&
             ( (boardPosition.row < boardSize) && (boardPosition.column < boardSize) ) );
}

bool choiceTaken(TicTacToeSquare &gameSquare)
{
    return (gameSquare.state != TTTS_Blank);
}

bool squareMatches(TicTacToeSquare &gameBoard, SquareState choiceCheck, int row, int column)
{
    Position boardPosition = { row, column };
    TicTacToeSquare *currentSquare = getSquare(boardPosition, &gameBoard);
    return (currentSquare->state == choiceCheck);
}

bool boardIsFull(TicTacToeSquare *gameBoard)
{
    TicTacToeSquare *p_current = gameBoard;
    while (p_current != nullptr)
    {
        if ((p_current->state == TTTS_Blank))
        {
            return false;
        }
        p_current = p_current->next;
    }
    return true;
}

string translateEnumToString(SquareState squareState)
{
    switch (squareState)
    {
    case TTTS_Blank:
        return " ";
    case TTTS_O:
        return "O";
    case TTTS_X:
        return "X";
    default:
        return "~";
    }
}

SquareState choiceSquare(bool playerXInSession)
{
    if (playerXInSession)
    {
        return TTTS_X;
    }
    return TTTS_O;
}

void setChoice(TicTacToeSquare *gameSquare, bool playerXInSession)
{
    gameSquare->state = choiceSquare(playerXInSession);
}

void drawBoard(int size, TicTacToeSquare &gameBoard)
{
    cout << "Tic-Tac-Toe\n";
    cout << minToWin << "-in-a-row are needed to win!\n";
    string horizontalBar = " _";
    for (int row = 0; row < size; row++)
    {
        horizontalBar += "__";
    }

    for (int row = 0; row <= size; row++)
    {
        if (row == 0)
        {
            for (int column = 0; column <= size; column++)
            {
                if (column == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << " " << column;
                }
            }
            cout << "\n";
        }
        else
        {
            cout << horizontalBar << "\n";
            for (int column = 0; column <= size; column++)
            {
                if (column == 0)
                {
                    cout << row;
                }
                else
                {
                    Position boardPosition = { row - 1, column - 1 };
                    TicTacToeSquare *currentSquare = getSquare(boardPosition, &gameBoard);
                    cout << "|" << translateEnumToString(currentSquare->state);
                }
            }
            cout << "|\n";
        }
    }
    cout << horizontalBar << "\n\n";
}

bool choiceWins(bool playerXInSession, TicTacToeSquare &gameBoard, int size)
{
    SquareState choiceCheck = choiceSquare(playerXInSession);;
    double score;

    for (int row = 0; row < size; row++)
    {
        score = 0;
        for (int column = 0; column < size; column++)
        {
            if (squareMatches(gameBoard, choiceCheck, row, column))
            {
                score++;
                if (score >= minToWin)
                {
                    return true;
                }
            }
            else
            {
                score = 0;
            }
        }
    }

    for (int column = 0; column < size; column++)
    {
        score = 0;
        for (int row = 0; row < size; row++)
        {
            if (squareMatches(gameBoard, choiceCheck, row, column))
            {
                score++;
                if (score >= minToWin)
                {
                    return true;
                }
            }
            else
            {
                score = 0;
            }
        }
    }

    score = 0;
    for (int i = 0; i < size; i++)
    {
        if (squareMatches(gameBoard, choiceCheck, i, i))
        {
            score++;
            if (score >= minToWin)
            {
                return true;
            }
        }
        else
        {
            score = 0;
        }
    }

    int maxIndex = size - 1;
    score = 0;
    for (int i = 0; i < size; i++)
    {
        if (squareMatches(gameBoard, choiceCheck, i, maxIndex - i))
        {
            score++;
            if (score >= minToWin)
            {
                return true;
            }
        }
        else
        {
            score = 0;
        }
    }

    return false;
}

int main(int argc, const char *argv[])
{
    try
    {
        bool gameFinished = false;
        bool playerXInSession = true;
        string player = "";
        int row = 0;
        int column = 0;

        int sizeUsed = 4;

        cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
        cout << "(Default is " << minToWin << ")\n";
        cin >> sizeUsed;
        if (sizeUsed < minToWin)
        {
            sizeUsed = minToWin;
        }

        TicTacToeSquare *gameBoard = createGameBoard(sizeUsed);

        do
        {
            row = 0;
            column = 0;
            player = setPlayer(playerXInSession);

            drawBoard(sizeUsed, *gameBoard);

            cout << "Player " << player << ", choose your next board position to claim:\n";

            cout << "Row: \n";
            cin >> row;
            row--;

            cout << "Column: \n";
            cin >> column;
            column--;

            Position boardPosition = { row, column };
            if (!validIndex(boardPosition, sizeUsed))
            {
                cout << "That is an invalid choice. Please try again.\n";
                continue;
            }

            TicTacToeSquare *currentSquare = getSquare(boardPosition, gameBoard);
            if (currentSquare == nullptr)
            {
                cout << "You have selected a position that does not exist on the board. Please try again.\n";
                continue;;
            }

            if (choiceTaken(*currentSquare))
            {
                cout << "That square is already taken. Please try again.\n";
                continue;
            }

            setChoice(currentSquare, playerXInSession);

            if (choiceWins(playerXInSession, *gameBoard, sizeUsed))
            {
                cout << "Player " << player << " wins!\n";
                gameFinished = true;
            }

            if (boardIsFull(gameBoard))
            {
                cout << "Board is full. The game is a tie!\n";
                gameFinished = true;
            }

            playerXInSession = !playerXInSession;
        }
        while (!gameFinished);

        if (gameBoard != nullptr)
        {
            TicTacToeSquare *p_current = gameBoard;
            TicTacToeSquare *p_next;
            while (p_current != nullptr)
            {
                p_next = p_current->next;
                delete p_current;
                p_current = p_next;
            }
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
