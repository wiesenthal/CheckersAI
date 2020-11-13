#include "StudentAI.h"
#include <random>
#include <cmath>

//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.

Board * getBoard(const Board & b,const Move & move, const int player) // gets a board
{
    Board * b2 = new Board(b);
    b2->makeMove(move, player);
    return b2;
}


StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

//Test- Ludo
Move StudentAI::GetMove(Move move)
{
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    int i = rand() % (moves.size());
    vector<Move> checker_moves = moves[i];
    int j = rand() % (checker_moves.size());
    Move res = checker_moves[j];
    board.makeMove(res,player);
    return res;


}

float StudentAI::simulate(const Node * pickedNode) {
    Board * board = new Board(*(pickedNode->board));
    int currPlayer = pickedNode->player;
    while (board->isWin(currPlayer) != 0) {
        vector<vector<Move>> moves = board->getAllPossibleMoves(currPlayer);
        // THIS IS NOT TRULY RANDOM, CHANGE SOON
        int i = rand() % (moves.size());
        vector<Move> checker_moves = moves[i];
        int j = rand() % (checker_moves.size());
        Move pickedMove = checker_moves[j];
        board->makeMove(pickedMove,currPlayer);
        currPlayer = currPlayer == 1 ? 2 : 1;
    }

    int winner = board->isWin(player);
    if (player == winner)
        return 1;
    if (winner == -1)
        return 0.5;
    return 0;
}

float StudentAI::getUCBValue(const Node * state) {
    //UCB(State) = averageValue + explorationConstant * sqrt(ln(parentN)/myN)
    float avgVal = state->winValue / (float) state->visitCount;
    float s = sqrt(log((float)state->parent->visitCount)/(float)state->visitCount);

    return avgVal + (exploration*s);
}

Node * StudentAI::getMaxUCB(Node * node) {
    float max = 0;
    Node * bestChild = nullptr;
    for (int i = 0; i < node->children.size(); i++) {
        if (getUCBValue(node->children[i]) > max) {
            max = getUCBValue(node->children[i]);
            bestChild = node->children[i];
        }
    }
    return bestChild;
}

Node * StudentAI::select(Node * node) {
    while (!node->children.empty()) {
        node = getMaxUCB(node);
    }
    return node;
}

Node::Node(Board * board1, Node * parent1) : board(board1), parent(parent1)
{}


