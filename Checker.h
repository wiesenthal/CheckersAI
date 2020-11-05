//
// Created by Ziyang Zhang on 2019-05-01.
//

#ifndef CHECKER_TEACHER_CHECKER_H
#define CHECKER_TEACHER_CHECKER_H

#include <vector>
#include <map>
#include <string>
#include <set>
#include "Utils.h"
#include "Move.h"
using namespace std;

class Board;
class Checker
{
public:
    string color;
    int  row, col;
    static const map<string , string> opponent;
    bool isKing;
    Checker(string color,int x,int y);
    void becomeKing();
    void becomeMan();
    vector<Move> getPossibleMoves(Board*board);
    void binary_tree_traversal(int pos_x,int pos_y,vector<vector<Position> > & multiple_jump,Board& board,vector<Position> direction,vector<Position>move,string self_color);
    string toString();

};


#endif //CHECKER_TEACHER_CHECKER_H
