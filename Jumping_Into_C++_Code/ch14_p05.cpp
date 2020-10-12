#include <iostream>
#include <string>

using namespace std;

enum ConnectFourSquare
{
    C4_Blank,
    C4_Plus,
    C4_X
};

struct BoardCoordinate
{
    int X;
    int Y;
};

ConnectFourSquare **createGameBoard(int boardWidth, int boardHeight);
void printBoard(ConnectFourSquare **gameBoard, int boardWidth, int boardHeight);
string setPlayer(bool playerXInSession);
string translateEnumToString(ConnectFourSquare squareState);
bool validIndex(BoardCoordinate boardPosition, int boardWidth, int boardHeight);
bool choiceTaken(BoardCoordinate boardPosition, ConnectFourSquare **gameBoard);
void setChoice(BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, bool playerXInSession);
ConnectFourSquare choiceSquare(bool playerXInSession);
bool choiceWins(bool playerXInSession, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight);
bool choiceWinsDiagonalDownRight(ConnectFourSquare choiceCheck, BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight);
bool choiceWinsDiagonalUpRight(ConnectFourSquare choiceCheck, BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight);
bool boardIsFull(ConnectFourSquare **gameBoard, int boardWidth, int boardHeight);

void disposeArray2D(ConnectFourSquare **p_p_array2D, int arrayWidth);

int const minToWin = 4;

int main()
{
    bool gameFinished = false;
    bool playerXInSession = true;
    string player = "";
    int row = 0;
    int column = 0;

    const int boardWidth = 7;
    const int boardHeight = 6;

    ConnectFourSquare **gameBoard = createGameBoard(boardWidth, boardHeight);

    do
    {
        row = 0;
        column = 0;
        player = setPlayer(playerXInSession);

        printBoard(gameBoard, boardWidth, boardHeight);

        cout << "Player " << player << ", choose your next board position to claim:\n";

        cout << "Row: \n";
        cin >> row;
        row--;

        cout << "Column: \n";
        cin >> column;
        column--;

        BoardCoordinate boardPosition;
        boardPosition.X = row;
        boardPosition.Y = column;

        if (!validIndex(boardPosition, boardWidth, boardHeight))
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

        if (choiceWins(playerXInSession, gameBoard, boardWidth, boardHeight))
        {
            cout << "Player " << player << " wins!\n";
            gameFinished = true;
        }

        if (boardIsFull(gameBoard, boardWidth, boardHeight))
        {
            cout << "Board is full. The game is a tie!\n";
            gameFinished = true;
        }

        playerXInSession = !playerXInSession;
    }
    while (!gameFinished);

    disposeArray2D(gameBoard, boardWidth);
}

void disposeArray2D(ConnectFourSquare **p_p_array2D, int arrayWidth)
{
    for (size_t j = 0; j < arrayWidth; j++)
    {
        delete[] p_p_array2D[j];
    }

    delete[] p_p_array2D;
}

void printBoard(ConnectFourSquare **gameBoard, int boardWidth, int boardHeight)
{
    cout << "Connect Four\n";
    cout << minToWin << "-in-a-row are needed to win!\n";
    string horizontalBar = " _";

    for (int i = 0; i < boardHeight; i++)
    {
        horizontalBar += "__";
    }

    for (int i = 0; i <= boardWidth; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j <= boardHeight; j++)
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
            for (int j = 0; j <= boardHeight; j++)
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
}

ConnectFourSquare **createGameBoard(int boardWidth, int boardHeight)
{
    ConnectFourSquare **gameBoard = new ConnectFourSquare*[boardWidth];
    for (int i = 0; i < boardWidth; i++)
    {
        gameBoard[i] = new ConnectFourSquare[boardHeight];
    }

    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardHeight; j++)
        {
            gameBoard[i][j] = C4_Blank;
        }
    }
    return gameBoard;
}

string setPlayer(bool playerXInSession)
{
    if (playerXInSession)
    {
        return "X";
    }
    return "+";
}

bool validIndex(BoardCoordinate boardPosition, int boardWidth, int boardHeight)
{
    return ( ( (boardPosition.X >= 0) && (boardPosition.Y >= 0) ) &&
            ( (boardPosition.X < boardWidth) && (boardPosition.Y < boardHeight) ) );
}

bool choiceTaken(BoardCoordinate boardPosition, ConnectFourSquare **gameBoard)
{
    return (gameBoard[boardPosition.X][boardPosition.Y] != C4_Blank);
}

void setChoice(BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, bool playerXInSession)
{
    gameBoard[boardPosition.X][boardPosition.Y] = choiceSquare(playerXInSession);
}

ConnectFourSquare choiceSquare(bool playerXInSession)
{
    if (playerXInSession)
    {
        return C4_X;
    }
    return C4_Plus;
}

bool choiceWins(bool playerXInSession, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight)
{
    ConnectFourSquare choiceCheck = choiceSquare(playerXInSession);;
    double score;

    for (int i = 0; i < boardWidth; i++)
    {
        score = 0;
        for (int j = 0; j < boardHeight; j++)
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

    for (int j = 0; j < boardHeight; j++)
    {
        score = 0;
        for (int i = 0; i < boardWidth; i++)
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

    BoardCoordinate boardPositionsDownRight[6];
    boardPositionsDownRight[0].X = 0;
    boardPositionsDownRight[0].Y = 2;

    boardPositionsDownRight[1].X = 0;
    boardPositionsDownRight[1].Y = 1;

    boardPositionsDownRight[2].X = 0;
    boardPositionsDownRight[2].Y = 0;

    boardPositionsDownRight[3].X = 1;
    boardPositionsDownRight[3].Y = 0;

    boardPositionsDownRight[4].X = 2;
    boardPositionsDownRight[4].Y = 0;

    boardPositionsDownRight[5].X = 3;
    boardPositionsDownRight[5].Y = 0;

    for (int i = 0; i < 6; i++)
    {
        if (choiceWinsDiagonalDownRight(choiceCheck, boardPositionsDownRight[i], gameBoard, boardWidth, boardHeight))
        {
            return true;
        }
    }

    BoardCoordinate boardPositionsUpRight[6];
    boardPositionsUpRight[0].X = 0;
    boardPositionsUpRight[0].Y = 3;

    boardPositionsUpRight[1].X = 0;
    boardPositionsUpRight[1].Y = 4;

    boardPositionsUpRight[2].X = 0;
    boardPositionsUpRight[2].Y = 5;

    boardPositionsUpRight[3].X = 1;
    boardPositionsUpRight[3].Y = 5;

    boardPositionsUpRight[4].X = 2;
    boardPositionsUpRight[4].Y = 5;

    boardPositionsUpRight[5].X = 3;
    boardPositionsUpRight[5].Y = 5;

    for (int i = 0; i < 6; i++)
    {
        if (choiceWinsDiagonalUpRight(choiceCheck, boardPositionsUpRight[i], gameBoard, boardWidth, boardHeight))
        {
            return true;
        }
    }

    return false;
}

bool choiceWinsDiagonalDownRight(ConnectFourSquare choiceCheck, BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight)
{
    int score = 0;
    while (validIndex(boardPosition, boardWidth, boardHeight))
    {
        if (gameBoard[boardPosition.X][boardPosition.Y] == choiceCheck)
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
        boardPosition.X++;
        boardPosition.Y++;
    }
    return false;
}

bool choiceWinsDiagonalUpRight(ConnectFourSquare choiceCheck, BoardCoordinate boardPosition, ConnectFourSquare **gameBoard, int boardWidth, int boardHeight)
{
    int score = 0;
    while (validIndex(boardPosition, boardWidth, boardHeight))
    {
        if (gameBoard[boardPosition.X][boardPosition.Y] == choiceCheck)
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
        boardPosition.X++;
        boardPosition.Y--;
    }
    return false;
}



bool boardIsFull(ConnectFourSquare **gameBoard, int boardWidth, int boardHeight)
{
    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardHeight; j++)
        {
            if (gameBoard[i][j] == C4_Blank)
            {
                return false;
            }
        }
    }
    return true;
}

string translateEnumToString(ConnectFourSquare squareState)
{
    switch (squareState)
    {
    case C4_Blank:
        return " ";
    case C4_Plus:
        return "+";
    case C4_X:
        return "X";
    default:
        return "~";
    }
}
