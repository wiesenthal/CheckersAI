#include "StudentAI.h"
#include <random>

//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
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

float Node::simulate(const Node * pickedNode, const int player) {
    Board * board = new Board(pickedNode->board);

    while (board->isWin(player) != 0) {
        vector<vector<Move>> moves = node->board.getAllPossibleMoves(player);
        int i = rand() % (moves.size());
        vector<Move> checker_moves = moves[i];
        int j = rand() % (checker_moves.size());
        Move pickedMove = checker_moves[j];
        board.makeMove(pickedMove,player);
    }

    int winner = board->isWin(player);
    if (player == winner)
        return 1;
    if (winner == -1)
        return 0.5;
    return 0;
}

Board * getBoard(const Board & b,const Move & move, const int player) // gets a board
{
    Board * b2 = new Board(b);
    b2->makeMove(move, player);
    return b2;
}

Node::Node(Board board1, Node * parent1) : board() : parent(parent1)
{}


