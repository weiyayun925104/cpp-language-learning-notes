#pragma once
#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <string>

using namespace std;

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

#endif
