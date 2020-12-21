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

enum CheckersSquare
{
    Checkers_Filled,
    Checkers_NotFilled,
    Checkers_SinglePiece_Black,
    Checkers_KingPiece_Black,
    Checkers_SinglePiece_Red,
    Checkers_KingPiece_Red
};

enum CheckersPlayers
{
    CheckersPlayers_Black,
    CheckersPlayers_Red
};

enum CheckersMoves
{
    CheckersMoves_ForwardLeft = 1,
    CheckersMoves_ForwardRight = 2,
    CheckersMoves_BackwardLeft = 3,
    CheckersMoves_BackwardRight = 4
};

int const maxBoardSize = 50;
int const minBoardSize = 10;

int const maxPieces = 500;
int const minPieces = 20;

bool isEven(int number)
{
    return (number % 2 == 0);
}

bool isOdd(int number)
{
    return !isEven(number);
}

bool isValidSquare(int row, int column)
{
    return ( ( isEven(row) && isOdd(column) ) || ( isOdd(row) && isEven(column) ) );
}

void populateGameBoard(CheckersSquare array[][50], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (isValidSquare(i, j))
            {
                array[i][j] = Checkers_Filled;
            }
            else
            {
                array[i][j] = Checkers_NotFilled;
            }
        }
    }
}

void populateBlackPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces)
{
    int currentPlayerPiece = 1;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if ( (currentPlayerPiece <= numberOfPieces) &&
                    ( isValidSquare(i, j) ) )
            {
                playerPieces[i][j] = Checkers_SinglePiece_Black;
                currentPlayerPiece++;
            }
            else
            {
                playerPieces[i][j] = Checkers_NotFilled;
            }
        }
    }
}

void populateRedPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces)
{
    int currentPlayerPiece = 1;

    for (int i = boardSize - 1; i >= 0 ; i--)
    {
        for (int j = boardSize - 1; j >= 0; j--)
        {
            if ( (currentPlayerPiece <= numberOfPieces) &&
                    ( isValidSquare(i, j) ) )
            {
                playerPieces[i][j] = Checkers_SinglePiece_Red;
                currentPlayerPiece++;
            }
            else
            {
                playerPieces[i][j] = Checkers_NotFilled;
            }
        }
    }
}

string translateEnumToString(CheckersSquare squareState)
{
    switch (squareState)
    {
    case Checkers_Filled:
        return "#";
    case Checkers_NotFilled:
        return " ";
    case Checkers_SinglePiece_Red:
        return "x";
    case Checkers_KingPiece_Red:
        return "X";
    case Checkers_SinglePiece_Black:
        return "o";
    case Checkers_KingPiece_Black:
        return "O";
    default:
        return "~";
    }
}

string translateEnumToString(CheckersPlayers squareState)
{
    switch (squareState)
    {
    case CheckersPlayers_Black:
        return "O";
    case CheckersPlayers_Red:
        return "X";
    default:
        return "~";
    }
}

void drawBoard(CheckersSquare gameBoard[][50], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    cout << "Checkers\n";
    cout << "Black (O) Side\n";
    string horizontalBar = " _";
    for (int i = 0; i < boardSizeUsed; i++)
    {
        horizontalBar += "__";
    }

    for (int i = 0; i <= boardSizeUsed; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j <= boardSizeUsed; j++)
            {
                if (j == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << " " << j;
                }
            }
            cout << "\n";
        }
        else
        {
            cout << horizontalBar << "\n";
            for (int j = 0; j <= boardSizeUsed; j++)
            {
                if (j == 0)
                {
                    cout << i;
                }
                else
                {
                    string squareCharacter;
                    if (playerPieces[i - 1][j - 1] != Checkers_NotFilled)
                    {
                        squareCharacter = translateEnumToString(playerPieces[i - 1][j - 1]);
                    }
                    else if (oppositionPieces[i - 1][j - 1] != Checkers_NotFilled)
                    {
                        squareCharacter = translateEnumToString(oppositionPieces[i - 1][j - 1]);
                    }
                    else
                    {
                        squareCharacter = translateEnumToString(gameBoard[i - 1][j - 1]);
                    }

                    cout << "|" << squareCharacter;
                }
            }
            cout << "|\n";
        }
    }
    cout << "Red (X) Side\n";
    cout << horizontalBar << "\n\n";
}

CheckersPlayers setPlayer(CheckersPlayers playerBlackInSession)
{
    if (playerBlackInSession == CheckersPlayers_Red)
    {
        return CheckersPlayers_Black;
    }
    return CheckersPlayers_Red;
}

CheckersPlayers getPlayer(CheckersSquare playerPiece)
{
    if ((playerPiece == Checkers_SinglePiece_Black) || (playerPiece == Checkers_KingPiece_Black))
    {
        return CheckersPlayers_Black;
    }
    return CheckersPlayers_Red;
}

bool isPieceKing(CheckersSquare playerPiece)
{
    return ((playerPiece == Checkers_KingPiece_Black) || (playerPiece == Checkers_KingPiece_Red));
}

void getMoveOffset(CheckersPlayers player, CheckersMoves move, int moveOffset[2])
{
    switch (move)
    {
    case CheckersMoves_ForwardLeft:
        moveOffset[0] = 1;
        moveOffset[1] = 1;
        break;
    case CheckersMoves_ForwardRight:
        moveOffset[0] = 1;
        moveOffset[1] = -1;
        break;
    case CheckersMoves_BackwardLeft:
        moveOffset[0] = -1;
        moveOffset[1] = 1;
        break;
    case CheckersMoves_BackwardRight:
        moveOffset[0] = -1;
        moveOffset[1] = -1;
        break;
    default:
        moveOffset[0] = 0;
        moveOffset[1] = 0;
        break;
    }

    int direction = 1;
    if (player == CheckersPlayers_Red)
    {
        direction = -1;
    }

    moveOffset[0] = moveOffset[0] * direction;
    moveOffset[1] = moveOffset[1] * direction;
}

bool isInBounds(int row, int column, int boardSizeUse)
{
    return ( (0 <= row) && (row < boardSizeUse) &&
             (0 <= column) && (column < boardSizeUse) );
}

bool moveIsOntoOppositionPiece(int landingRow, int landingColumn, CheckersSquare oppositionPieces[][50])
{
    CheckersSquare neighboringOpposingPiece = oppositionPieces[landingRow][landingColumn];
    return (neighboringOpposingPiece != Checkers_NotFilled);
}

bool moveIsValid(int boardPosition[], int offset[], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    int landingRow = boardPosition[0] + offset[0];
    int landingColumn = boardPosition[1] + offset[1];

    if (!isInBounds(landingRow, landingColumn, boardSizeUsed))
    {
        return false;
    }

    CheckersSquare neighboringPlayerPiece = playerPieces[landingRow][landingColumn];
    if (neighboringPlayerPiece != Checkers_NotFilled)
    {
        return false;
    }

    if (moveIsOntoOppositionPiece(landingRow, landingColumn, oppositionPieces))
    {
        landingRow += offset[0];
        landingColumn += offset[1];

        if (!isInBounds(landingRow, landingColumn, boardSizeUsed))
        {
            return false;
        }

        CheckersSquare landingSquareOpposition = oppositionPieces[landingRow][landingColumn];
        CheckersSquare landingSquarePlayer = playerPieces[landingRow][landingColumn];
        if ( (landingSquareOpposition != Checkers_NotFilled) ||
                (landingSquarePlayer != Checkers_NotFilled) )
        {
            return false;
        }
    }
    return true;
}

bool isValidPosition(int boardPosition[], CheckersPlayers player, CheckersSquare playerPieces[][50])
{
    if (player == CheckersPlayers_Black)
    {
        return ( (playerPieces[ boardPosition[0] ][ boardPosition[1] ] == Checkers_SinglePiece_Black) ||
                 (playerPieces[ boardPosition[0] ][ boardPosition[1] ] == Checkers_KingPiece_Black) );
    }

    if (player == CheckersPlayers_Red)
    {
        return ( (playerPieces[ boardPosition[0] ][ boardPosition[1] ] == Checkers_SinglePiece_Red) ||
                 (playerPieces[ boardPosition[0] ][ boardPosition[1] ] == Checkers_KingPiece_Red) );
    }

    return false;
}

bool isPieceTrapped(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed)
{
    CheckersSquare playerPiece = playerPieces[boardPosition[0]][boardPosition[1]];
    CheckersPlayers player = getPlayer(playerPiece);
    bool isCurrentPieceKing = isPieceKing(playerPiece);

    int maxEnum = 2;
    if (isCurrentPieceKing)
    {
        maxEnum = 4;
    }
    int tempMove[2];
    for (int i = 1; i <= maxEnum; i++)
    {
        getMoveOffset(player, static_cast<CheckersMoves>(i), tempMove);
        if (moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces))
        {
            return false;
        }
    }

    return true;
}

void getBoardPosition(int boardPosition[], int boardSizeUsed, CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    int startRow = 0;
    int startColumn = 0;
    bool isCurrentValidPosition;

    do
    {
        cout << "Player " << translateEnumToString(player) << ", choose the piece to move:\n";

        cout << "Row: \n";
        cin >> startRow;
        startRow--;
        boardPosition[0] = startRow;

        cout << "Column: \n";
        cin >> startColumn;
        startColumn--;
        boardPosition[1] = startColumn;

        cout << '\n';
        isCurrentValidPosition = isValidPosition(boardPosition, player, playerPieces);
        if (!isCurrentValidPosition)
        {
            cout << "Position chosen is invalid. \n";
            cout << "Please choose a row/column locating the piece to move.\n";
            continue;
        }

        isCurrentValidPosition = !isPieceTrapped(boardPosition, playerPieces, oppositionPieces, boardSizeUsed);
        if (!isCurrentValidPosition)
        {
            cout << "Piece chosen is trapped! \n";
            cout << "Please choose a different piece.\n";
            continue;
        }
    }
    while (!isCurrentValidPosition);
}

void chooseBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPiece, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    int moveChoice = 0;
    int tempMove[2];
    bool isCurrentValidMove = false;
    CheckersPlayers player = getPlayer(playerPiece);

    bool isCurrentPieceKing = isPieceKing(playerPiece);
    int maxEnum = 2;
    if (isCurrentPieceKing)
    {
        maxEnum = 4;
    }

    string pieceType = "regular";
    if (isCurrentPieceKing)
    {
        pieceType = "king";
    }

    do
    {
        cout << "Player " << translateEnumToString(player) << ", choose where to move the " << pieceType << " piece in reference to your starting side and direction:\n";
        cout << "1: Forward-Left\n";
        cout << "2: Forward-Right\n";
        if (isCurrentPieceKing)
        {
            cout << "3: Backward-Left\n";
            cout << "4: Backward-Right\n";
        }
        cin >> moveChoice;

        if (moveChoice < 1 || moveChoice > maxEnum)
        {
            cout << "Please enter a valid move number.\n";
            continue;
        }

        getMoveOffset(player, static_cast<CheckersMoves>(moveChoice), tempMove);

        isCurrentValidMove = moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces);
        if (!isCurrentValidMove)
        {
            cout << "\n" << "Move will land piece out of bounds, or onto an occupied square." << "\n";
            cout << "Please choose another move." << "\n";
        }
    }
    while (!isCurrentValidMove);

    boardMove[0] = tempMove[0];
    boardMove[1] = tempMove[1];
}

bool pieceCanJumpNeighboringPiece(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed)
{
    CheckersSquare playerPiece = playerPieces[boardPosition[0]][boardPosition[1]];
    CheckersPlayers player = getPlayer(playerPiece);
    bool isCurrentPieceKing = isPieceKing(playerPiece);

    int maxEnum = 2;
    if (isCurrentPieceKing)
    {
        maxEnum = 4;
    }
    int tempMove[2];
    for (int i = 1; i <= maxEnum; i++)
    {
        getMoveOffset(player, static_cast<CheckersMoves>(i), tempMove);
        if (moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces))
        {
            return true;
        }
    }

    return false;
}

bool isOnBoardTopBottomEdge(int row, int boardSizeUsed)
{
    return ((row == 0) || (row == (boardSizeUsed - 1)));
}

void kingPiece(int row, int column, CheckersSquare playerPieces[][50])
{
    CheckersSquare currentPiece = playerPieces[row][column];
    if (currentPiece == Checkers_SinglePiece_Black)
    {
        playerPieces[row][column] = Checkers_KingPiece_Black;
    }
    if (currentPiece == Checkers_SinglePiece_Red)
    {
        playerPieces[row][column] = Checkers_KingPiece_Red;
    }
}

bool makeBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPieces[][50],  CheckersSquare oppositionPieces[][50])
{
    int landingRow = boardPosition[0] + boardMove[0];
    int landingColumn = boardPosition[1] + boardMove[1];
    bool continueTurn = false;
    bool pieceWasJumped = false;

    if (moveIsOntoOppositionPiece(landingRow, landingColumn, oppositionPieces))
    {
        oppositionPieces[landingRow][landingColumn] = Checkers_NotFilled;
        pieceWasJumped = true;
        cout << "A piece was just jumped!\n";

        landingRow += boardMove[0];
        landingColumn += boardMove[1];

        continueTurn = true;
    }

    CheckersSquare currentPiece = playerPieces[ boardPosition[0] ][ boardPosition[1] ];
    playerPieces[ boardPosition[0] ][ boardPosition[1] ] = Checkers_NotFilled;
    playerPieces[landingRow][landingColumn] = currentPiece;
    boardPosition[0] = landingRow;
    boardPosition[1] = landingColumn;

    if (pieceWasJumped)
    {
        continueTurn = pieceCanJumpNeighboringPiece(boardPosition, playerPieces, oppositionPieces, boardSizeUsed);
    }

    if (isOnBoardTopBottomEdge(landingRow, boardSizeUsed))
    {
        if (!isPieceKing(currentPiece))
        {
            kingPiece(landingRow, landingColumn, playerPieces);
            cout << "Piece is upgraded to a king!\n";
        }
        continueTurn = false;
    }

    return continueTurn;
}

bool areAllOppositionPiecesEliminated(int boardSizeUsed, CheckersSquare oppositionPieces[][50])
{
    for (int i = 0; i < boardSizeUsed; i++)
    {
        for (int j = 0; j < boardSizeUsed; j++)
        {
            if (oppositionPieces[i][j] != Checkers_NotFilled)
            {
                return false;
            }
        }
    }
    return true;
}

bool areAllOppositionPiecesTrapped(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    for (int i = 0; i < boardSizeUsed; i++)
    {
        for (int j = 0; j < boardSizeUsed; j++)
        {
            if (oppositionPieces[i][j] != Checkers_NotFilled)
            {
                int boardPosition[2] = { i, j };
                if (!isPieceTrapped(boardPosition, oppositionPieces, playerPieces, boardSizeUsed))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool choiceWins(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
    return (areAllOppositionPiecesEliminated(boardSizeUsed, oppositionPieces) || areAllOppositionPiecesTrapped(boardSizeUsed, playerPieces, oppositionPieces));
}

bool isTurnWinning(int boardPosition[], int boardMove[], CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], CheckersSquare gameBoard[][50], int boardSizeUsed)
{
    getBoardPosition(boardPosition, boardSizeUsed, player, playerPieces, oppositionPieces);
    CheckersSquare playerPiece = playerPieces[ boardPosition[0] ][ boardPosition[1] ];

    bool nextPlayer;
    do
    {
        chooseBoardMove(boardPosition, boardMove, boardSizeUsed, playerPiece, playerPieces, oppositionPieces);
        nextPlayer = !makeBoardMove(boardPosition, boardMove, boardSizeUsed, playerPieces, oppositionPieces);
        drawBoard(gameBoard, boardSizeUsed, playerPieces, oppositionPieces);

        if (choiceWins(boardSizeUsed, playerPieces, oppositionPieces))
        {
            cout << "Player " << translateEnumToString(player) << " wins!\n";
            return true;
        }
    }
    while (!nextPlayer);
    return false;
}

int main(int argc, const char *argv[])
{
    try
    {
        int boardSizeUsed = minBoardSize;
        int numberOfPiecesUsed = minPieces;

        CheckersSquare gameBoard[maxBoardSize][maxBoardSize];
        populateGameBoard(gameBoard, maxBoardSize);

        CheckersSquare BlackPieces[maxBoardSize][maxBoardSize];
        populateBlackPieces(boardSizeUsed, BlackPieces, numberOfPiecesUsed);

        CheckersSquare RedPieces[maxBoardSize][maxBoardSize];
        populateRedPieces(boardSizeUsed, RedPieces, numberOfPiecesUsed);

        CheckersPlayers player = CheckersPlayers_Black;

        bool gameFinished = false;
        int boardPosition[2];
        int boardMove[2];
        drawBoard(gameBoard, boardSizeUsed, BlackPieces, RedPieces);
        do
        {
            if (player == CheckersPlayers_Black)
            {
                gameFinished = isTurnWinning(boardPosition, boardMove, player, BlackPieces, RedPieces, gameBoard, boardSizeUsed);
            }
            else
            {
                gameFinished = isTurnWinning(boardPosition, boardMove, player, RedPieces, BlackPieces, gameBoard, boardSizeUsed);
            }

            player = setPlayer(player);
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
