#include "Move.h"


Move::Move()
{
}

Move::Move(const Move & move)
{
    this->seq = move.seq;
}

Move::Move(const vector<Position> seq)
{
    this->seq = seq;
}

Move::Move(const string & input)
{
    int len = input.length();
    if (input == "-1"){
        return;
    }

    string delimiter = "-";
    vector<string> points = split(input,delimiter);
    for (int i = 0; i<points.size();++i)
    {
        string point = points[i];
        string result;
        for (int j = 1; j<point.length()-1;++j)
        {
            result += point[j];
        }
        vector<string> xy = split(result,",");
        int x = stoi(xy[0]);
        int y = stoi(xy[1]);
        Position coordinate{x,y};
        seq.push_back(coordinate);


    }

}

vector<string> Move::split(string input,const string delimiter){
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    result.push_back(input);
    return result;
}

string Move::toString()
{
    string result;
    for (int i = 0;i<seq.size();++i)
    {
        result += "("+to_string(seq[i][0])+","+to_string(seq[i][1])+")";
        if (i != seq.size()-1)
        {
            result += "-";
        }
    }
    return result;
}

bool Move::isCapture()
{
    if (this->seq.size()>2)
        return true;
    return abs(seq[0][0]-seq[1][0]) > 1;
}