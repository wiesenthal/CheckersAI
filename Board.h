#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include "Move.h"
#include "Checker.h"

using namespace std;

struct Saved_Move{
    Move maked_move;
    vector<vector<int>> saved_enemy_list; //<row, col, color(1/2 indicate "B"/"W", is_king>
    bool become_king;
};

class Board {
public:
	vector<vector<Checker> > board;
    static const map<string , string> opponent;
	int col, row, p, blackCount,whiteCount,tieCount,tieMax;
    vector<Saved_Move> saved_move_list;
	Board();
	Board(int col, int row,int p);
    void initializeGame ();
    bool isInBoard(int pos_x,int pos_y);
    bool isValidMove(int chess_row, int chess_col, int target_row, int target_col, string turn);
    void checkInitialVariable();
    vector<vector<Move> > getAllPossibleMoves(string color);
    vector<vector<Move> > getAllPossibleMoves(int player);
    void makeMove(const Move& move,int player);
	int isWin(int turn);
	int isWin(string turn);
	void Undo();
	void showBoard();

};








class InvalidMoveError : public exception
{

};

class InvalidParameterError : public exception
{

};



#endif //BOARD_H
