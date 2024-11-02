#include "bishop.hpp"

Bishop::Bishop(string color){
    this->_value = 3.0f;
    this->_id = 4;
    this->_setColor(color);
    if (this->_isWhite)
        this->_symbol = "♝";
    else
        this->_symbol = "♗";
}

vector<pmove> Bishop::PossibleMoves(Board &board, int x, int y){
    vector<pmove> Result;
    bool am_i_white = board.board[x][y]->isWhite();

    struct side {
        int dir_x;
        int dir_y;
    };

    vector<side> sides = {
        {1, -1}, //up-left
        {1, 1}, //up-right
        {-1, 1}, //down-right
        {-1, -1} //down-left
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