#include "knight.hpp"


Knight::Knight(string color){
    this->_value = 3.0f;
    this->_id = 3;
    this->_setColor(color);
    if (this->_isWhite)
        this->_symbol = "♞";
    else
        this->_symbol = "♘";
}

vector<pmove> Knight::PossibleMoves(Board &board, int x, int y){
    vector<pmove> Result;
    bool am_i_white = board.board[x][y]->isWhite(); 

    vector<pmove> relative_positions = {
        {2, -1},
        {2, 1},
        {1, 2},
        {-1, 2},
        {-2, -1},
        {-2, 1},
        {1, -2},
        {-1, -2}
    };
    for (auto & pos : relative_positions){
        int new_x = x + pos.x;
        int new_y = y + pos.y;
        if (!this->checkLimits(new_x, new_y))
            continue;
        
        //simple move
        if (board.IsEmpty(new_x, new_y)){
            Result.push_back({new_x, new_y, 0});
        //takes
        } else if(board.IsWhite(new_x, new_y) != am_i_white){
            Result.push_back({new_x, new_y, 1});
        }
        
    }

    return Result;
}


