#include "Board.h"

const map<string , string> Board::opponent = {{"W","B"},{"B","W"}};

Board::Board()
{
    col = 0;
    row = 0;
    p = 0;
    this->blackCount = 0;
    this->whiteCount = 0;
}
Board::Board(int col, int row,int p)
{
    this->col = col;
    this->row = row;
    this->p = p;
    this->blackCount = 0;
    this->whiteCount = 0;
    this->tieCount = 0;
    this->tieMax = 40;
    this->board = vector<vector<Checker> >(row);
    for (int i = 0;i < row; ++i)
    {
        for (int j = 0;j<col;++j)
        {
            board[i].push_back(Checker(".",i,j));
        }
    }

}


void Board::showBoard()
{
    cout << setw(2) << " ";
    for (int j = 0; j < col; ++j)
    {
        cout << setw(3) << j;
    }
    cout<<endl;

    for (int i = 0; i < this->row; ++i)
    {
        cout << i << "|" ;
        for (int j = 0; j < col; ++j)
        {
            cout << setw(3) << this->board[i][j].toString();
        }
        cout << endl;
    }
    for (int j = 0; j < col; ++j)
    {
        cout << "----";
    }
    cout << endl;

}

void Board::initializeGame(){
    this->checkInitialVariable();
    for (int i = this->p; i >= 0; i--)
    {
        for (int j = (this->p - i - 1) % 2; j >= 0 && j < this->col; j += 2)
        {
            // put white pieces
            int i_white = this->row - this->p + i;
            this->board[i_white][j] = Checker("W", i_white, j);
            // put black pieces
            if ((this->row % 2 + this->p % 2) % 2 == 1)  // row,k = even,odd or odd,even
            {
                if (i % 2 == 1)  // even row, shift to the left and attach a peice to the end when needed
                {
                    if (j - 1 >= 0)
                        this->board[i][j-1] = Checker("B", i, j-1);
                    if ((j == this->col -2) && (this->col % 2 == 0))
                        this->board[i][this->col-1] = Checker("B", i, this->col-1);
                } else {  // odd row, shift to the right and attach a piece to the beginning when needed
                    if (j + 1 <= this->col -1)
                        this->board[i][j+1] = Checker("B", i, j+1);
                    if ((j == this->col - 1 || j == this->col - 2) && (this->p % 2 == 0))
                        this->board[i][0] = Checker("B", i, 0);
                }
            } else {  // row,p = even,even
                this->board[i][j] = Checker("B", i, j);
            }
            this->blackCount++;
            this->whiteCount++;
        }
    }
}

void Board::checkInitialVariable() {
    // Recently changed: return false is changed to raising exceptions
    // Q > 0
    if (row - 2 * p <= 0)
    {
        cerr<<"Q <= 0"<<endl;
        throw  InvalidParameterError();
    }
    //M = 2P + Q
    else if (row != 2 * p + (row - 2 * p))
    {
        cerr<<"M != 2P + Q"<<endl;
        throw InvalidParameterError();
    }
    // N*P is even
    else if (col * p % 2 != 0)
    {

        cerr<<"N*P is odd"<<endl;
        throw InvalidParameterError();
    }

}

bool Board::isValidMove(int chess_row, int chess_col, int target_row, int target_col, string turn)
{
    if (target_row < 0||target_row >= this->row||target_col < 0||target_col >= this->col)

        return false;
    if  (! (this->board[target_row][target_col].color == "."))

        return false;
    if  (! (this->board[chess_row][chess_col].color == turn))

        return false;
    int diff_col = target_col - chess_col;
    int diff_row = target_row - chess_row;
    if (abs(diff_col) != abs(diff_row))
        return false;
    Checker chess_being_moved = this->board[chess_row][chess_col];
    if (diff_row == 1 && diff_col == 1)
        return chess_being_moved.isKing||chess_being_moved.color == "B";
    if (diff_row == 1 && diff_col == -1)
        return chess_being_moved.isKing||chess_being_moved.color == "B";
    if (diff_row == -1 && diff_col == 1  )
        return chess_being_moved.isKing||chess_being_moved.color == "W";
    if (diff_row == -1 && diff_col == -1  )
        return chess_being_moved.isKing||chess_being_moved.color == "W";
    if (diff_row == 2 && diff_col == 2 )
        return (chess_being_moved.isKing||chess_being_moved.color == "B") && this->board[chess_row + 1][chess_col + 1].color != turn && this->board[chess_row + 1][chess_col + 1].color != ".";
    if (diff_row == 2 && diff_col == -2 )
        return (chess_being_moved.isKing||chess_being_moved.color == "B") && this->board[chess_row + 1][chess_col - 1].color != turn && this->board[chess_row + 1][chess_col - 1].color != ".";
    if (diff_row == -2 && diff_col == 2 )
        return (chess_being_moved.isKing||chess_being_moved.color == "W") && this->board[chess_row - 1][chess_col + 1].color != turn && this->board[chess_row - 1][chess_col + 1].color != ".";
    if (diff_row == -2 && diff_col == -2 )
        return (chess_being_moved.isKing||chess_being_moved.color == "W") && this->board[chess_row - 1][chess_col - 1].color != turn && this->board[chess_row - 1][chess_col - 1].color != ".";
    return false;

}

vector<vector<Move> > Board::getAllPossibleMoves(string color) {
    vector<vector<Move> > temp;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Checker checker = board[i][j];
            if (checker.color == color) {
                vector<Move> moves;
                moves = checker.getPossibleMoves(this);
                if (!moves.empty())
                    temp.push_back(moves);
            }

        }
    }
    bool hasCapture = false;
    vector<vector<Move> > result;
    int cursorToResult = 0;
    for (int cursorToTemp = 0; cursorToTemp < temp.size(); ++cursorToTemp)
    {
        vector<Move> VectorI;
        result.push_back(VectorI);
        for (int j = 0; j < temp[cursorToTemp].size(); ++j)
        {
            if (! hasCapture)
            {
                if (temp[cursorToTemp][j].isCapture())
                {
                    hasCapture = true;
                    result.clear();
                    vector<Move> firstVector;
                    firstVector.push_back(temp[cursorToTemp][j]);
                    result.push_back(firstVector);
                    cursorToResult = 0;
                }
                else{
                    result[cursorToResult].push_back(temp[cursorToTemp][j]);
                }
            }
            else{
                if (temp[cursorToTemp][j].isCapture())
                {
                    result[cursorToResult].push_back(temp[cursorToTemp][j]);
                }
            }

        }
        if (result[cursorToResult].size() == 0 )
        {
            result.erase(result.begin() + cursorToResult);
            --cursorToResult;
        }
        ++cursorToResult;
    }
    return result;
}

vector<vector<Move> > Board::getAllPossibleMoves(int player) {
    vector<vector<Move> > temp;
    string color = player == 1?"B" : "W";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Checker checker = board[i][j];
            if (checker.color == color) {
                vector<Move> moves;
                moves = checker.getPossibleMoves(this);
                if (!moves.empty())
                    temp.push_back(moves);
            }

        }
    }
    bool hasCapture = false;
    vector<vector<Move> > result;
    int cursorToResult = 0;
    for (int cursorToTemp = 0; cursorToTemp < temp.size(); ++cursorToTemp)
    {
        vector<Move> VectorI;
        result.push_back(VectorI);
        for (int j = 0; j < temp[cursorToTemp].size(); ++j)
        {
            if (! hasCapture)
            {
                if (temp[cursorToTemp][j].isCapture())
                {
                    hasCapture = true;
                    result.clear();
                    vector<Move> firstVector;
                    firstVector.push_back(temp[cursorToTemp][j]);
                    result.push_back(firstVector);
                    cursorToResult = 0;
                }
                else{
                    result[cursorToResult].push_back(temp[cursorToTemp][j]);
                }
            }
            else{
                if (temp[cursorToTemp][j].isCapture())
                {
                    result[cursorToResult].push_back(temp[cursorToTemp][j]);
                }
            }

        }
        if (result[cursorToResult].size() == 0 )
        {
            result.erase(result.begin() + cursorToResult);
            --cursorToResult;
        }
        ++cursorToResult;
    }
    return result;
}

bool Board::isInBoard(int pos_x, int pos_y)
{
    return pos_x >= 0 && pos_x < row && pos_y >= 0 && pos_y < col;
}

void Board::makeMove(const Move& move, int player)
{
    //DO NOT TOUCH ANYTHING IN THIS FUNCTION
    //THE CODE LOGIC IS FROM PYTHON VERSION
    Saved_Move temp_saved_move;
    temp_saved_move.maked_move = move;
    
    vector<vector<int>> saved_enemy_position;
    string turn = "";

    if (player == 1)
        turn = "B";
    else if (player == 2)
        turn = "W";
    else {
        throw InvalidMoveError();
    }
    vector<Position> move_list = move.seq;
    vector<vector<Position> > move_to_check;
    Position ultimate_start = move_list[0];
    bool is_start_checker_king = this->board[ultimate_start[0]][ultimate_start[1]].isKing;
    Position ultimate_end = move_list[move_list.size()-1];
    vector<Position> past_positions{ultimate_start};
    vector<Position> capture_positions;
    for (int i = 0;i<move_list.size()-1;++i)
        move_to_check.push_back(vector<Position>{move_list[i],move_list[i + 1]});

    bool if_capture = false;
    this->tieCount += 1;
    for (int t = 0; t<move_to_check.size();++t){
        Position  start = move_to_check[t][0];
        Position target= move_to_check[t][1];
        if (this->isValidMove(start[0],start[1],target[0],target[1],turn) || (if_capture  && abs(start[0]-target[0]) == 1)){
            this->board[start[0]][start[1]].color = ".";
            this->board[target[0]][target[1]].color = turn;
            this->board[target[0]][target[1]].isKing = this->board[start[0]][start[1]].isKing;
            this->board[start[0]][start[1]].becomeMan();
            past_positions.push_back(target);
            if (abs(start[0]-target[0]) == 2)
            {
                vector<int> temp_enemy_position;
                if_capture = true;
                this->tieCount = 0;
                Position capture_position {(start[0] + (int)(target[0]-start[0])/2), (start[1] + (int)(target[1]-start[1])/2)};
                if(turn == "B")
                    this->whiteCount--;
                else
                    this->blackCount--;

                capture_positions.push_back(capture_position);
                //record capture position
                temp_enemy_position.push_back(capture_position[0]); // row
                temp_enemy_position.push_back(capture_position[1]); // col
                // push back color 1 = "B" 2 = "W"
                if(this->board[capture_position[0]][capture_position[1]].color == "B"){
                    temp_enemy_position.push_back(1);
                }
                else{
                    temp_enemy_position.push_back(2);
                }
                // the checker is regular or king, 0 = regular, 1 = king
                if(this->board[capture_position[0]][capture_position[1]].isKing){
                    temp_enemy_position.push_back(1);
                }
                else{temp_enemy_position.push_back(0);}
                
                saved_enemy_position.push_back(temp_enemy_position);
                
                this->board[capture_position[0]][capture_position[1]] = Checker(".", capture_position[0], capture_position[1]);
                
                
            }
            if (turn == "B"  && target[0] == this->row - 1){
                if(!is_start_checker_king){
                    temp_saved_move.become_king = true;
                }
                else{
                    temp_saved_move.become_king = false;
                }
                
                this->board[target[0]][target[1]].becomeKing();
                if (!is_start_checker_king){
                        break;
                }
            }
            
            else if (turn == "W"  && target[0] == 0){
                if(!is_start_checker_king){
                    temp_saved_move.become_king = true;
                }
                else{
                    temp_saved_move.become_king = false;
                }
                
                this->board[target[0]][target[1]].becomeKing();
                if (!is_start_checker_king){
                        break;
                }
            }
            else{
                temp_saved_move.become_king = false;
            }
        }
        else {
            throw InvalidMoveError();
        }

    }
    temp_saved_move.saved_enemy_list = saved_enemy_position;
    saved_move_list.push_back(temp_saved_move);

}


int Board::isWin(int turn) {
    if (this->tieCount >= this->tieMax){
        return -1;
    }
    bool W = true;
    bool B = true;
    if (getAllPossibleMoves(1).size() == 0) {
        if (turn != 1)
            B = false;
    } else if (getAllPossibleMoves(2).size() == 0) {
        if (turn != 2)
            W = false;
    } else {
        for (int row = 0; row < this->row; row++) {
            for (int col = 0; col < this->col; col++) {
                Checker checker = this->board[row][col];
                if (checker.color == "W")
                    W = false;
                else if (checker.color == "B")
                    B = false;
                if (!W && !B)
                    return 0;
            }
        }
    }
    if (W)
        return 2;
    else if (B)
        return 1;
    else
        return 0;
}

int Board::isWin(string turn_s) {
    if (this->tieCount >= this->tieMax){
        return -1;
    }
    bool W = true;
    bool B = true;
    bool WHasMove = true;
    bool BHasMove = true;
    int turn = 0;
    if (turn_s == "W")
        turn = 2;
    else if (turn_s == "B")
        turn = 1;
    if (getAllPossibleMoves(1).size() == 0) {
        if (turn != 1)
            BHasMove = false;
    } else if (getAllPossibleMoves(2).size() == 0) {
        if (turn != 2)
            WHasMove = false;
    }
    if (WHasMove && !BHasMove)
    {
        return 2;
    }
    else if  (!WHasMove && BHasMove)
    {
        return 1;
    }
    for (int row = 0; row < this->row; row++) {
        for (int col = 0; col < this->col; col++) {
            Checker checker = this->board[row][col];
            if (checker.color == "W")
                W = false;
            else if (checker.color == "B")
                B = false;
            if (!W && !B)
                return 0;
        }
    }

    if (W)
        return 2;
    else if (B)
        return 1;
    else
        return 0;
}


void Board:: Undo(){
    if(!saved_move_list.empty()){
        Saved_Move temp_saved_move = saved_move_list.back();
        Position original_point = temp_saved_move.maked_move.seq[0];
        Position target_point = temp_saved_move.maked_move.seq[temp_saved_move.maked_move.seq.size()-1];
        
        this->board[original_point[0]][original_point[1]].color = this->board[target_point[0]][target_point[1]].color;
        if(temp_saved_move.become_king){
            this->board[original_point[0]][original_point[1]].isKing = false;
        }
        else{
            this->board[original_point[0]][original_point[1]].isKing = this->board[target_point[0]][target_point[1]].isKing;
        }
        
        if(!(target_point == original_point)){
            this->board[target_point[0]][target_point[1]].color = ".";
            this->board[target_point[0]][target_point[1]].isKing = false;
        }
        for(int i = 0; i < temp_saved_move.saved_enemy_list.size(); i++){
            int x = temp_saved_move.saved_enemy_list[i][0];
            int y = temp_saved_move.saved_enemy_list[i][1];
            int c = temp_saved_move.saved_enemy_list[i][2];
            int k = temp_saved_move.saved_enemy_list[i][3];
            
            this->board[x][y].color = (c==1?"B":"W");
            this->board[x][y].isKing = (k==0?false:true);

            }
        this->tieCount -= 1;
        saved_move_list.pop_back();
        
        
    }
    this->blackCount = 0;
    this->whiteCount = 0;
    for (int row = 0; row < this->row; row++) {
        for (int col = 0; col < this->col; col++) {
            if (this->board[row][col].color == "W")
            {
                this->whiteCount++;
            }
            else if (this->board[row][col].color == "B")
            {
                 this->blackCount++;
            }
            
        }
    }
}



