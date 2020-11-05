#include "GameLogic.h"

GameLogic::GameLogic(int col, int row, int p, string mode,int order)
{
	this->col = col;
	this->row = row;
	this->p = p;
	this->mode = mode;
	this->order = order;
	this->aiList = new vector<AI*>();
}

void GameLogic::Manual()
{
	int player = 1;
	int winPlayer = 0;
	bool init = true;
	Move move;
	Board board(col, row, p);
        board.initializeGame();
        board.showBoard();
	while (true)
	{
		move = ((*aiList)[player - 1])->GetMove(move);
		cout << move.toString() << endl;
		try
		{
			board.makeMove(move, player);
		}
		catch (InvalidMoveError)
		{
			cerr << "Invalid Move!" << endl;
			winPlayer = player == 1 ? 2 : 1;
			break;
		}
		winPlayer = board.isWin(player);
		board.showBoard();
		if (winPlayer != 0)
		{
			break;
		}
		player = player == 1 ? 2 : 1;

	}
	if (winPlayer == -1)
	{
	    cout<< "Tie"<<endl;
	}
	else
	{
	    cout << "Player " << winPlayer << " wins!" << endl;
	}

}

void GameLogic::TournamentInterface()
{
	StudentAI ai(col, row, p);
	while (true)
	{
		string instr;
		cin >> instr;
		Move result = ai.GetMove(Move(instr));
		cout << result.toString()<< endl;
	}
}

void GameLogic::Run()
{
	if (mode == "m" or mode == "manual")
	{
        AI* studentai = new StudentAI(col, row, p);
        AI* manualai = new ManualAI(col, row, p);
		if (order == 1)
        	{
            		aiList->push_back(manualai);
            		aiList->push_back(studentai);
        	}
        	else
        	{
            		aiList->push_back(studentai);
          	  	aiList->push_back(manualai);
        	}

		Manual();
	}
	else if (mode == "s" or mode == "self")
	{
		AI* studentai = new StudentAI(col, row, p);
        AI* manualai = new StudentAI(col, row, p);
		if (order == 1)
        	{
            		aiList->push_back(manualai);
            		aiList->push_back(studentai);
        	}
        	else
        	{
            		aiList->push_back(studentai);
          	  	aiList->push_back(manualai);
        	}

		Manual();
	}
	else if (mode == "t")
	{
		TournamentInterface();
	}
}



GameLogic::~GameLogic()
{
	while(!aiList->empty())
	{
		delete aiList->back();
		aiList->pop_back();
	}
}
