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
        Node(Board *, Node *, int);
        Board * board;
        Node * parent;
        vector<Node *> children;
        float winValue;
        int visitCount;
        int player;

};

Board * getBoard(const Board &, const Move &, const int); // make an action, returns new board

class StudentAI :public AI
{
public:
    Board board;
    StudentAI(int col, int row, int p);
    virtual Move GetMove(Move board);

    const float exploration = 1;

    //Our functions
    Node * chooseBest(Node *); //return node at the end of MCTS to make final move
    Node * select(Node *); //return node to explore
    Node * getMaxUCB(Node *); //return child node with highest UCB value

    float getUCBValue(const Node *); //get the UCB value of one board state
    float simulate(const Node *); // rollout from a leaf node to get to the end with random nodes
    void backpropogate(Node *, float); // update values from the leaf node up, given the value returned by simulate


};


#endif //STUDENTAI_H
