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

enum SquareState
{
    TTTS_Blank,
    TTTS_O,
    TTTS_X
};

struct Position
{
    int row = 0;
    int column = 0;
};

struct TicTacToeSquare
{
    SquareState state = TTTS_Blank;
    Position position;
};

class TicTacToeBoard
{
public:
    static int const minToWin = 4;
    static int const maxSize = 50;
    int size = maxSize;

    void populateGameBoard();
    string setPlayer(bool playerXInSession);

    bool validIndex(Position boardPosition);
    bool choiceTaken(Position boardPosition);
    void setChoice(Position boardPosition);

    bool choiceWins();
    bool boardIsFull();

    void drawBoard();

private:
    bool _playerXInSession = true;
    TicTacToeSquare _gameBoard[maxSize][maxSize];

    static TicTacToeSquare createSquare(int row, int column, SquareState state);
    TicTacToeSquare getSquare(Position boardPosition);
    SquareState choiceSquare();
    static string translateEnumToString(SquareState squareState);
};

void TicTacToeBoard::populateGameBoard()
{
    for (int i = 0; i < maxSize; i++)
    {
        for (int j = 0; j < maxSize; j++)
        {
            _gameBoard[i][j] = createSquare(i, j, TTTS_Blank);
        }
    }
}

TicTacToeSquare TicTacToeBoard::createSquare(int row, int column, SquareState state)
{
    TicTacToeSquare newSquare;
    newSquare.position.row = row;
    newSquare.position.row = column;
    newSquare.state = state;

    return newSquare;
}

TicTacToeSquare TicTacToeBoard::getSquare(Position boardPosition)
{
    if (validIndex(boardPosition))
    {
        return _gameBoard[boardPosition.row][boardPosition.column];
    }
    TicTacToeSquare empty;
    return empty;
}

string TicTacToeBoard::setPlayer(bool playerXInSession)
{
    _playerXInSession = playerXInSession;
    if (_playerXInSession)
    {
        return "X";
    }
    return "O";
}

bool TicTacToeBoard::validIndex(Position boardPosition)
{
    return ( ( (boardPosition.row >= 0) && (boardPosition.column >= 0) ) &&
             ( (boardPosition.row < size) && (boardPosition.column < size) ) );
}

bool TicTacToeBoard::choiceTaken(Position boardPosition)
{
    return (_gameBoard[boardPosition.row][boardPosition.column].state != TTTS_Blank);
}

void TicTacToeBoard::setChoice(Position boardPosition)
{
    _gameBoard[boardPosition.row][boardPosition.column].state = choiceSquare();
}

SquareState TicTacToeBoard::choiceSquare()
{
    if (_playerXInSession)
    {
        return TTTS_X;
    }
    return TTTS_O;
}

bool TicTacToeBoard::choiceWins()
{
    SquareState choiceCheck = choiceSquare();;
    double score;

    for (int i = 0; i < size; i++)
    {
        score = 0;
        for (int j = 0; j < size; j++)
        {
            if (_gameBoard[i][j].state == choiceCheck)
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

    for (int j = 0; j < size; j++)
    {
        score = 0;
        for (int i = 0; i < size; i++)
        {
            if (_gameBoard[i][j].state == choiceCheck)
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
        if (_gameBoard[i][i].state == choiceCheck)
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

    score = 0;
    int maxIndex = size - 1;
    for (int i = 0; i < size; i++)
    {
        if (_gameBoard[i][maxIndex - i].state == choiceCheck)
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

bool TicTacToeBoard::boardIsFull()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (_gameBoard[i][j].state == TTTS_Blank)
            {
                return false;
            }
        }
    }
    return true;
}

string TicTacToeBoard::translateEnumToString(SquareState squareState)
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

void TicTacToeBoard::drawBoard()
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
                    Position boardPosition;
                    boardPosition.row = row - 1;
                    boardPosition.column = column - 1;
                    TicTacToeSquare currentSquare = getSquare(boardPosition);
                    cout << "|" << translateEnumToString(currentSquare.state);
                }
            }
            cout << "|\n";
        }
    }
    cout << horizontalBar << "\n\n";
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
        TicTacToeBoard gameBoard;

        cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
        cout << "(Default is " << gameBoard.minToWin << " and max is " << gameBoard.maxSize << ")\n";
        cin >> sizeUsed;
        cin.clear();
        cin.ignore(80, '\n');

        if (sizeUsed < gameBoard.minToWin)
        {
            sizeUsed = gameBoard.minToWin;
        }
        if (sizeUsed > gameBoard.maxSize)
        {
            sizeUsed = gameBoard.maxSize;
        }

        gameBoard.size = sizeUsed;
        gameBoard.populateGameBoard();

        do
        {
            row = 0;
            column = 0;
            player = gameBoard.setPlayer(playerXInSession);

            gameBoard.drawBoard();

            cout << "Player " << player << ", choose your next board position to claim:\n";

            cout << "Row: \n";
            cin >> row;
            cin.clear();
            cin.ignore(80, '\n');
            row--;

            cout << "Column: \n";
            cin >> column;
            cin.clear();
            cin.ignore(80, '\n');
            column--;

            Position boardPosition;
            boardPosition.row = row;
            boardPosition.column = column;

            if (!gameBoard.validIndex(boardPosition))
            {
                cout << "That is an invalid choice. Please try again.\n";
                continue;
            }

            if (gameBoard.choiceTaken(boardPosition))
            {
                cout << "That square is already taken. Please try again.\n";
                continue;
            }

            gameBoard.setChoice(boardPosition);

            if (gameBoard.choiceWins())
            {
                cout << "Player " << player << " wins!\n";
                gameFinished = true;
            }
            else if (gameBoard.boardIsFull())
            {
                cout << "Board is full. The game is a tie!\n";
                gameFinished = true;
            }

            playerXInSession = !playerXInSession;
        }
        while (!gameFinished);

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
