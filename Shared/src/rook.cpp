#include "rook.hpp"


Rook::Rook(string color){
    this->_value = 5.0f;
    this->_id = 2;
    this->_setColor(color);
    if (this->_isWhite)
        this->_symbol = "♜";
    else
        this->_symbol = "♖";
}

vector<pmove> Rook::PossibleMoves(Board &board, int x, int y){
    vector<pmove> Result;
    bool am_i_white = board.board[x][y]->isWhite();

    struct side {
        int dir_x;
        int dir_y;
    };

    vector<side> sides = {
        {1, 0}, //up
        {-1, 0}, //down
        {0, 1}, //right
        {0, -1} //left
    };


    for (auto &side : sides){
        int new_x = x + side.dir_x;
        int new_y = y + side.dir_y;
        //simple move
        while (this->checkLimits(new_x, new_y) && board.IsEmpty(new_x, new_y)){
            Result.push_back({new_x, new_y, 0});
            new_x += side.dir_x;
            new_y += side.dir_y;
        }
        //takes
        if (this->checkLimits(new_x, new_y) && board.IsWhite(new_x, new_y) != am_i_white){
            Result.push_back({new_x, new_y, 1});
        }
    }

  
    return Result;
}

