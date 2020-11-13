#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <vector>

using namespace std;
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class Node {
public:
    Node(Board, Node *);
    Board board;
    Node * parent;
    vector<Node *> children;
    double winValue;
    int visitCount;

};

class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);
	Board getBoard(Board, Move);
	float getUCBValue(Node *);
};



#endif //STUDENTAI_H
