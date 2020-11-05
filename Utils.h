//
// Created by Ziyang Zhang on 2019-05-03.
//

#ifndef CHECKER_TEACHER_UTILS_H
#define CHECKER_TEACHER_UTILS_H

#include <exception>
#include <vector>
#include <map>
#include <string>

class Position {
public:
    int x;
    int y;
    Position(int x,int y);
    int& operator[] (const int& index);
    bool operator== (const Position& lp) const;
    bool operator< (const Position& rp) const;
};

class Direction {
public:
    const std::map<std::string, const std::vector< Position> > list
    {{"W",std::vector<Position>{Position(-1,-1),Position(-1,1)}},{"B",std::vector< Position>{Position(1,-1),Position(1,1)}} };
    std::vector<Position> operator[] (const std::string& index);
    Direction() = default;
};

class IndexOutOfBoundError : public std::exception {

};

#endif //CHECKER_TEACHER_UTILS_H
