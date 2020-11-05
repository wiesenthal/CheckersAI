#ifndef MOVE_H
#define MOVE_H

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Utils.h"
using namespace std;
class Move
{
public:
	vector<Position> seq;
	Move();
    Move(const Move & move);
    Move(const vector<Position> seq);
    Move(const string & input);
    vector<string> split(string input,string delimiter);
    string toString();
    bool isCapture();
};

class MoveBuildError : public std::exception
{

};
#endif //MOVE_H
