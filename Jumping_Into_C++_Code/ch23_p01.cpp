#include <iostream>
#include <string>
#include "TicTacToe.h"

using namespace std;

int main()
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
}
