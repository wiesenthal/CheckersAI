#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "AI.h"
#include "Board.h"
#include "StudentAI.h"
#include "ManualAI.h"
#pragma once


class GameLogic
{
private:
	int col, row, p,order;
	string mode;
	vector<AI*> *aiList;
public:
	GameLogic(int col,int row,int p,string mode,int order);
	void Manual();
	void TournamentInterface();
	void Run();
	~GameLogic();
};

#endif //GAMELOGIC_H
