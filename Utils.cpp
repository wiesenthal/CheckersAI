//
// Created by Ziyang Zhang on 2019-05-03.
//

#include "Utils.h"

Position::Position(int x,int y)
    :x(x),y(y)
{
}

int& Position::operator[] (const int& index)
{
    if (index == 0)
    {
        return this->x;
    }
    else if (index == 1)
    {
        return this->y;
    }
    else
    {
        throw IndexOutOfBoundError();
    }
}

bool Position::operator== (const Position& lp) const
{
    return lp.x == x && lp.y == y;
}

bool Position::operator< (const Position& rp) const
{
    if (x < rp.x)
    {
        return true;
    }
    else if (x == rp.x)
    {
        if (y <  rp.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }



}


std::vector<Position> Direction::operator[] (const std::string& index)
{
    return list.at(index);
}
