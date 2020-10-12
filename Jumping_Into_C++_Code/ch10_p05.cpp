#include <iostream>
#include <string>

using namespace std;

enum TicTacToeSquare
{
    TTTS_Blank,
    TTTS_O,
    TTTS_X
};

#define MAXBOARDSIZE 8

void populateGameBoard(enum TicTacToeSquare array[][MAXBOARDSIZE], int size);
string setPlayer(bool playerXInSession);
string translateEnumToString(enum TicTacToeSquare squareState);
bool validIndex(int boardPosition[], int boardSize);
bool choiceTaken(int boardPosition[], enum TicTacToeSquare gameBoard[][MAXBOARDSIZE]);
void setChoice(int boardPosition[], enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], bool playerXInSession);
enum TicTacToeSquare choiceSquare(bool playerXInSession);
bool choiceWins(bool playerXInSession, enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], int size);
bool boardIsFull(enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], int size);

int const minToWin = 4;

int main()
{
    bool gameFinished = false;
    bool playerXInSession = true;
    string player = "";
    int row = 0;
    int column = 0;

    int const size = MAXBOARDSIZE;
    int sizeUsed = 4;

    cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
    cout << "(Default is " << minToWin << ")\n";
    cin >> sizeUsed;
    if (sizeUsed < minToWin)
    {
        sizeUsed = minToWin;
    }
    if (sizeUsed > size)
    {
        sizeUsed = size;
    }

    enum TicTacToeSquare gameBoard[size][size];
    populateGameBoard(gameBoard, size);

    do
    {
        row = 0;
        column = 0;
        player = setPlayer(playerXInSession);

        cout << "Tic-Tac-Toe\n";
        cout << minToWin << "-in-a-row are needed to win!\n";
        string horizontalBar = " _";
        for (int i = 0; i < sizeUsed; i++)
        {
            horizontalBar += "__";
        }

        for (int i = 0; i <= sizeUsed; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j <= sizeUsed; j++)
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
                for (int j = 0; j <= sizeUsed; j++)
                {
                    if (j == 0)
                    {
                        cout << i;
                    }
                    else
                    {
                        cout << "|" << translateEnumToString(gameBoard[i - 1][j - 1]);
                    }
                }
                cout << "|\n";
            }
        }
        cout << horizontalBar << "\n\n";

        cout << "Player " << player << ", choose your next board position to claim:\n";

        cout << "Row: \n";
        cin >> row;
        row--;

        cout << "Column: \n";
        cin >> column;
        column--;

        int boardPosition[2] = {row, column};

        if (!validIndex(boardPosition, sizeUsed))
        {
            cout << "That is an invalid choice. Please try again.\n";
            continue;
        }

        if (choiceTaken(boardPosition, gameBoard))
        {
            cout << "That square is already taken. Please try again.\n";
            continue;
        }

        setChoice(boardPosition, gameBoard, playerXInSession);

        if (choiceWins(playerXInSession, gameBoard, sizeUsed))
        {
            cout << "Player " << player << " wins!\n";
            gameFinished = true;
        }

        if (boardIsFull(gameBoard, sizeUsed))
        {
            cout << "Board is full. The game is a tie!\n";
            gameFinished = true;
        }

        playerXInSession = !playerXInSession;
    }
    while (!gameFinished);
}


void populateGameBoard(enum TicTacToeSquare array[][MAXBOARDSIZE], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            array[i][j] = TTTS_Blank;
        }
    }
}

string setPlayer(bool playerXInSession)
{
    if (playerXInSession)
    {
        return "X";
    }
    return "O";
}

bool validIndex(int boardPosition[], int boardSize)
{
    return ( ( (boardPosition[0] >= 0) && (boardPosition[1] >= 0) ) &&
            ( (boardPosition[0] < boardSize) && (boardPosition[1] < boardSize) ) );
}

bool choiceTaken(int boardPosition[], enum TicTacToeSquare gameBoard[][MAXBOARDSIZE])
{
    return (gameBoard[ boardPosition[0] ][ boardPosition[1] ] != TTTS_Blank);
}

void setChoice(int boardPosition[], enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], bool playerXInSession)
{
    gameBoard[ boardPosition[0] ][ boardPosition[1] ] = choiceSquare(playerXInSession);
}

enum TicTacToeSquare choiceSquare(bool playerXInSession)
{
    if (playerXInSession)
    {
        return TTTS_X;
    }
    return TTTS_O;
}

bool choiceWins(bool playerXInSession, enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], int size)
{
    enum TicTacToeSquare choiceCheck = choiceSquare(playerXInSession);;
    double score;

    for (int i = 0; i < size; i++)
    {
        score = 0;
        for (int j = 0; j < size; j++)
        {

            if (gameBoard[i][j] == choiceCheck)
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
            if (gameBoard[i][j] == choiceCheck)
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
        if (gameBoard[i][i] == choiceCheck)
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
        if (gameBoard[i][maxIndex - i] == choiceCheck)
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

bool boardIsFull(enum TicTacToeSquare gameBoard[][MAXBOARDSIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (gameBoard[i][j] == TTTS_Blank)
            {
                return false;
            }
        }
    }
    return true;
}

string translateEnumToString(enum TicTacToeSquare squareState)
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
