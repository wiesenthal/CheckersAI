#ifndef AI_H
#define AI_H
#include "Move.h"
#include "Board.h"
#pragma once

class AI
{
protected:
	int col, row, p, player;
public:

	AI(int col, int row, int p)
	{
		this->col = col;
		this->row = row;
		this->p = p;
	}
	virtual Move GetMove(Move move) = 0;
	virtual ~AI(){}
};

#endif //AI_H
