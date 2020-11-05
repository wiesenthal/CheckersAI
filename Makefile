make: mt
mt:main.cpp Board.cpp Board.h StudentAI.cpp StudentAI.h ManualAI.cpp ManualAI.h Move.cpp Move.h GameLogic.cpp GameLogic.h
	g++ -std=c++11 Utils.cpp Checker.cpp main.cpp Board.cpp StudentAI.cpp ManualAI.cpp Move.cpp GameLogic.cpp -o main
