//
// Created by Ziyang Zhang on 2019-05-01.
//

#include "Checker.h"
#include "Board.h"

const map<string , string> Checker::opponent = {{"W","B"},{"B","W"}};

Checker::Checker(string color, int row, int col) {
    color = (int)color[0] <= 90? color : string("")+(char) ((int)color[0]-32);
    this->color = color;
    this->row = row;
    this->col = col;
    this->isKing = false;

}

void Checker::becomeKing(){
    this->isKing = true;
};

void Checker::becomeMan(){
    this->isKing = false;
};

string Checker::toString() {
    if (isKing){
        return color;
    }
    else
    {
        return color == "." ? color :  string("")+(char) ((int)color[0]+32);
    }
}

vector<Move> Checker::getPossibleMoves(Board* board)
{
    Direction direction;
    vector<Move> result;
    if (this->color == ".")
    {
        return result;
    }
    vector<vector<Position>> multiple_jump;

    vector<Position> explore_direction = direction[color];
    if (isKing)
    {
        for  (int i = 0; i<direction[opponent.at(color)].size(); i++)
        {
            explore_direction.push_back(direction[opponent.at(color)][i]);
        }
    }
    for (auto i = explore_direction.begin(); i != explore_direction.end(); i++) {
        int pos_x = row+(*i)[0];
        int pos_y = col+(*i)[1];
        if (board->isInBoard(pos_x,pos_y))
        {
            if (board->board[pos_x][pos_y].color == ".")
            {
                result.emplace_back(Move(vector<Position>{Position(row,col),Position(pos_x,pos_y)}));
            }
        }
    }
    vector<Position> temp_v;
    string self_color =  board->board[row][col].color;
    board->board[row][col].color = ".";
    binary_tree_traversal(row,col,multiple_jump, *board, explore_direction, temp_v,self_color);
    if (!multiple_jump.empty())
    {
        result.clear();
    }

    for (auto jump = multiple_jump.begin(); jump != multiple_jump.end(); jump++) {
        (*jump).insert((*jump).begin(),Position(row,col));
        result.emplace_back(Move(*jump));
    }

    board->board[row][col].color = self_color;
    return result;

}

void Checker::binary_tree_traversal(int pos_x,int pos_y,vector<vector<Position>> & multiple_jump,Board& board,vector<Position> direction,vector<Position>move, string self_color) {
    bool flag = true;
    for (auto i = direction.begin(); i != direction.end(); i++) {
        int temp_x = pos_x + (*i)[0];
        int temp_y = pos_y + (*i)[1];
        Position temp(temp_x, temp_y);
        if (board.isInBoard(temp_x, temp_y)
        && board.board[temp_x][temp_y].color == opponent.at(self_color)
            && board.isInBoard(temp_x + (*i)[0], temp_y + (*i)[1])
            && board.board[temp_x + (*i)[0]][temp_y + (*i)[1]].color == ".")
        {
            flag = false;
            break;
        }

    }
    if (flag) {
        if (!move.empty()) {
            multiple_jump.push_back(move);
            return;
        }

    }

    for (auto i = direction.begin(); i != direction.end(); i++) {
        int temp_x = pos_x + (*i)[0];
        int temp_y = pos_y + (*i)[1];
        Position temp(temp_x, temp_y);
        if (board.isInBoard(temp_x, temp_y) && board.board[temp_x][temp_y].color == opponent.at(self_color)){
            if (board.isInBoard(pos_x + (*i)[0] + (*i)[0], pos_y + (*i)[1] + (*i)[1]) &&
                board.board[pos_x + (*i)[0] + (*i)[0]][pos_y + (*i)[1] + (*i)[1]].color == ".") {
                Position temptemp{pos_x + (*i)[0] + (*i)[0], pos_y + (*i)[1] + (*i)[1]};
                string backup = board.board[pos_x + (*i)[0]][pos_y + (*i)[1]].color;
                board.board[pos_x + (*i)[0]][pos_y + (*i)[1]].color = ".";
                move.push_back(temptemp);
                this->binary_tree_traversal(temptemp[0], temptemp[1], multiple_jump, board, direction, move,self_color);
                move.pop_back();
                board.board[pos_x + (*i)[0]][pos_y + (*i)[1]].color = backup;
            }

        }

    }

}