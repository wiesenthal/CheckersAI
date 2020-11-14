#include "StudentAI.h"
#include <random>
#include <cmath>
#include <ctime>
#include <cfloat>

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
    //create root
    Node * rootState = new Node(&board, nullptr, player, move);

    time_t startTime = time(NULL);
    while (time(NULL) - startTime)
    {
        Node * unexploredLeaf = select(rootState);
        float terminalWin = simulate(unexploredLeaf);
        backpropogate(unexploredLeaf, terminalWin);
    }
    //vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    //int i = rand() % (moves.size());
    //vector<Move> checker_moves = moves[i];
    //int j = rand() % (checker_moves.size());
    //Move res = checker_moves[j];

    Node * best = chooseBest(rootState);
    Move result = movePath[best];
    board.makeMove(result,player);
    return result;


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
    return winner;
}

float StudentAI::getUCBValue(const Node * state) {
    //UCB(State) = averageValue + explorationConstant * sqrt(ln(parentN)/myN)
    if (state->visitCount == 0)
    {
        return FLT_MAX;
    }
    float avgVal = state->winValue / (float) state->visitCount;
    float s = sqrt(log((float)state->parent->visitCount)/(float)state->visitCount);

    return avgVal + (exploration*s);
}

void StudentAI::backpropogate(Node * state, float terminalPlayer) {
    float score;
    while (state->parent)
    {
        score = 0 + (terminalPlayer == -1)*0.5 + (terminalPlayer == state->player);
        state->winValue += score;
        state->visitCount += 1;
        state = state->parent;
    }
}

Node * StudentAI::getMaxUCB(Node * node) {
    float max = 0;
    Node * bestChild = nullptr;
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->visitCount == 0) //if we find an unexplored node, the UCB is effectively infinite
        {
            return node->children[i];
        }
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

    //Expand tree
    bool isRoot = node->parent == nullptr;
    vector<vector<Move>> moves = node->board->getAllPossibleMoves(node->player);
    int newPlayer = node->player == 1 ? 2 : 1;
    for (int i = 0;  i < moves.size(); i++) {
        for (int j = 0; j < moves[i].size(); j++){
            Board * newBoard = getBoard(*(node->board), moves[i][j], node->player);
            Node * newNode = new Node(newBoard, node, newPlayer);
            if (isRoot)
                movePath[newNode] = moves[i][j];
            node->children.push_back(newNode);
        }
    }

    return getMaxUCB(node);
}

Node *StudentAI::chooseBest(Node * node) {
    float max = 0;
    Node * bestChild;
    for (int i = 0; i < node->children.size(); i++) {

        if (node->children[i]->visitCount == 0) //if we find an unexplored node
        {
            continue; //ignore the node, this should never occur however
        }
        float avgVal = node->winValue / (float) node->visitCount;
        if (avgVal > max) {
            max = avgVal;
            bestChild = node->children[i];
        }
    }
    return bestChild;
}

Node::Node(Board * board1, Node * parent1, int player1) : board(board1), parent(parent1),
    winValue(0), visitCount(0), player(player1)
{}


