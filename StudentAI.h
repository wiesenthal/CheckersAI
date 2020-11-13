#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <vector>

using namespace std;
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);
};

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
	Board getBoard(const Board &, const Move &, const int);
	float getUCBValue(const Node *); //get the UCB value of one board state
	float simulate(const Node *); // rollout from a leaf node to get to the end with random nodes
	void backpropogate(Node *, float); // update values from the leaf node up, given the value returned by simulate

};



#endif //STUDENTAI_H
