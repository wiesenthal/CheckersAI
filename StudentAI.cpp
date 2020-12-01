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
    totalVisitCount = 0;


    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }

    //if (player == 1)
    //{
        Node *rootState = new Node(&board, nullptr, player);
        time_t startTime = time(nullptr);
        while (time(nullptr) - startTime < moveTime) {
            Node *unexploredLeaf = select(rootState);
            float score = simulate(unexploredLeaf);
            backpropogate(unexploredLeaf, score);
            totalVisitCount++;
        }


        Node *best = chooseBest(rootState);
        Move result = movePath[best];
        board.makeMove(result, player);

        //Cleanup
        destroyTree(rootState);
        return result;
    //}

    //create root

    /*
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    int i = rand() % (moves.size());
    vector<Move> checker_moves = moves[i];
    int j = rand() % (checker_moves.size());
    Move res = checker_moves[j];
    board.makeMove(res, player);
    return res;
     */


}

float StudentAI::simulate(const Node * pickedNode) {
    Board * board = new Board(*(pickedNode->board));
    int currPlayer = pickedNode->player;

    while (board->isWin(currPlayer) == 0) {
        vector<vector<Move>> moves = board->getAllPossibleMoves(currPlayer);
        //getting the best move using hueristic
        Move bestMove;
        float min_heuristic = FLT_MAX;

        for (vector<Move> ms : moves)
        {
            for (Move m : ms)
            {
                float hValue;
                Board * temp = getBoard(*board, m, currPlayer);
                temp->makeMove(m, currPlayer);

                //hValue is how many peices opponent has, we want to minimize
                hValue = boardHeuristic(temp, currPlayer, false);
                if (hValue < min_heuristic)
                {
                    min_heuristic = hValue;
                    bestMove = m;
                }
                delete temp;
            }
        }
        //Make the best huerstical move
        board->makeMove(bestMove,currPlayer);
        currPlayer = currPlayer == 1 ? 2 : 1;


        //Pick random move
        /*
        int i = rand() % (moves.size());
        vector<Move> checker_moves = moves[i];
        int j = rand() % (checker_moves.size());
        Move pickedMove = checker_moves[j];

        board->makeMove(pickedMove,currPlayer);
        currPlayer = currPlayer == 1 ? 2 : 1;

        */
    }

    int p = pickedNode->player;
    int vc = board->isWin(player);
    float heuristic =  boardHeuristic(board, p, true);
    delete board;



    if (p == vc)
    {
        return heuristic;
    }
    if (vc == -1)
    {
        return tieWeight;
    }
    else
    {
        return -(heuristic);
    }
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

void StudentAI::backpropogate(Node * state, float score) const {
    int myTurn = -1;
    while (state)
    {
        state->winValue += score * (score == tieWeight ? 1 : myTurn);
        //state ->winValue += 0 + ((int)score == -1)*tieWeight + ((int)score != state->player);
        state->visitCount += 1;
        state = state->parent;
        myTurn *= -1;
    }
}

Node * StudentAI::getMaxUCB(Node * node) {
    float max = -(FLT_MAX-2);
    Node * bestChild = node;

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
    if (node->visitCount > 0 || !node->parent) {
        bool isRoot = node->parent == nullptr;
        vector <vector<Move>> moves = node->board->getAllPossibleMoves(node->player);
        if (moves.empty())
        {
            return node;
        }
        int newPlayer = node->player == 1 ? 2 : 1;
        for (int i = 0; i < moves.size(); i++) {
            for (int j = 0; j < moves[i].size(); j++) {
                Board *newBoard = getBoard(*(node->board), moves[i][j], node->player);
                Node *newNode = new Node(newBoard, node, newPlayer);
                if (isRoot)
                {
                    movePath[newNode] = moves[i][j];
                }
                node->children.push_back(newNode);
            }
        }
        return getMaxUCB(node);
    }
    return node;


}

//comment
Node *StudentAI::chooseBest(Node * node) {
    float max = -(FLT_MAX-2);
    Node * bestChild;
    float avgVal;
    for (int i = 0; i < node->children.size(); i++) {

        if (node->children[i]->visitCount == 0) //if we find an unexplored node
        {
            continue; //ignore the node, this should never occur however
        }
        avgVal = (node->children[i])->winValue / (float) (node->children[i])->visitCount;
        //avgVal = (float) node->visitCount;
        if (avgVal > max) {
            max = avgVal;
            bestChild = node->children[i];
        }
    }
    return bestChild;
}

float StudentAI::boardHeuristic(const Board * b, int player, bool isEndState) {
    float player1Score = 0;
    float player2Score = 0;


    for (vector<Checker> checkers : b->board) {
        for (Checker checker : checkers) {
            int totalRows = b->row - 1;

            if (checker.color == "Black") {
                player1Score += 5 + (player == 1 ? checker.row : -(checker.row-totalRows)) + (checker.isKing ? 2 : 0);
            } else {
                player1Score += 5 + (player == 2 ? checker.row : -(checker.row-totalRows)) + (checker.isKing ? 2 : 0);
            }
        }
    }


    if (isEndState) {
        return player1Score + player2Score;
    }

    return (player == 1) ? player1Score: player2Score;
}


void StudentAI::destroyTree(Node * node) {
    //This should never happen
    if ( (node == nullptr) || (node == NULL)) {
        return;
    }

    for (int i = 0; i < node->children.size(); i ++) {
        destroyTree(node->children[i]);
    }

    //node is a leaf, time to destroy it
    if (node->parent != nullptr) {
        delete node->board;
    }
    delete node;
}

Node::Node(Board * board1, Node * parent1, int player1) : board(board1), parent(parent1),
    winValue(0), visitCount(0), player(player1)
{}


