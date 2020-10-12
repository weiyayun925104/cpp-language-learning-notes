#include <iostream>
#include <string>
#include "TicTacToe.h"

using namespace std;

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
